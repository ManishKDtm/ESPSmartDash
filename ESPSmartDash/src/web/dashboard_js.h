#pragma once
#include <Arduino.h>

const char DASH_JS[] PROGMEM = R"rawliteral(

function card(title){
 let c=document.createElement("div")
 c.className="card"
 let h=document.createElement("div")
 h.innerHTML="<b>"+title+"</b>"
 c.appendChild(h)
 return c
}

function load(){
 fetch('/widgets').then(r=>r.json()).then(d=>{
  let root=document.getElementById("widgets")
  root.innerHTML=""

  d.toggles.forEach(w=>{
    let c=card(w.name)
    let b=document.createElement("button")
    b.innerText="Toggle"
    b.onclick=()=>fetch('/control?pin='+w.pin)
    c.appendChild(b)
    root.appendChild(c)
  })

  d.sliders.forEach(w=>{
    let c=card(w.name)
    let s=document.createElement("input")
    s.type="range"; s.min=0; s.max=255; s.value=w.value
    s.onchange=()=>fetch('/slider?pin='+w.pin+'&val='+s.value)
    c.appendChild(s)
    root.appendChild(c)
  })

  d.gauges.forEach(g=>{
    let c=card(g.name)
    let val=document.createElement("div")
    val.className="gauge"
    val.id=g.name
    val.innerText=g.value
    c.appendChild(val)
    root.appendChild(c)
  })

 })
}

function updateSensors(){

 fetch('/sensors')
 .then(r=>r.json())
 .then(data=>{

  for(let k in data){

   let el=document.getElementById(k)

   if(el){
     el.innerText=data[k]
   }

  }

 })

}

setInterval(load,2000)
setInterval(updateSensors,2000)
load()

)rawliteral";