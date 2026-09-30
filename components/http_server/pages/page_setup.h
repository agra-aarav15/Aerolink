/* Getting Started page templates */
#include "router_config.h"

#if !CONFIG_ETH_UPLINK
/* Getting Started Page.
 * SETUP_CHUNK_HEAD is streamed verbatim (single literal % is fine).
 * SETUP_CHUNK_FORM is printf-formatted into a fixed stack buffer, so keep it
 * lean and double any literal % as %%. */
#define SETUP_CHUNK_HEAD "<!doctype html>\
<html lang='en'>\
<head>\
<meta charset='utf-8'>\
<meta name='viewport' content='width=device-width,initial-scale=1'>\
<meta name='color-scheme' content='dark'>\
<meta name='theme-color' content='#000000'>\
<title>AeroLink - Setup</title>\
<link rel='icon' href='/favicon.png'>\
<link href='https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&display=swap' rel='stylesheet'>\
<style>\
*{box-sizing:border-box;margin:0;padding:0}\
html{-webkit-text-size-adjust:100%}\
body{font-family:'Inter',system-ui,-apple-system,'Segoe UI',Roboto,Helvetica,Arial,sans-serif;background:#000;color:#eef1f6;color-scheme:dark;min-height:100vh;display:flex;flex-direction:column;align-items:center;padding:1.1rem 1rem calc(1.5rem + env(safe-area-inset-bottom))}\
body::before{content:'';position:fixed;inset:0;z-index:0;pointer-events:none;background:radial-gradient(700px 340px at 50% -120px,rgba(79,140,255,.22),transparent 70%),radial-gradient(520px 420px at 110% 110%,rgba(79,140,255,.07),transparent 70%)}\
#wrap{position:relative;z-index:1;width:100%;max-width:560px;margin:auto}\
a{color:#7fa9ff;text-decoration:none}\
a:hover{color:#aecbff}\
:focus-visible{outline:2px solid rgba(127,169,255,.8);outline-offset:2px}\
::selection{background:rgba(79,140,255,.35)}\
.topbar{display:flex;align-items:center;justify-content:space-between;min-height:32px;margin-bottom:.3rem}\
.brand{display:inline-flex;align-items:center;gap:.55rem;color:#e7ecf5;font-size:.74rem;font-weight:600;letter-spacing:.22em;text-transform:uppercase}\
:root{--logo:url('data:image/svg+xml,%3Csvg xmlns=%22http://www.w3.org/2000/svg%22 viewBox=%220 0 64 64%22%3E%3Crect width=%2264%22 height=%2264%22 rx=%2215%22 fill=%22%23070b14%22/%3E%3Cpath d=%22M18 47 32 17 46 47%22 fill=%22none%22 stroke=%22%234f8cff%22 stroke-width=%226.5%22 stroke-linecap=%22round%22 stroke-linejoin=%22round%22/%3E%3Cpath d=%22M24.5 37.5h15%22 stroke=%22%234f8cff%22 stroke-width=%226.5%22 stroke-linecap=%22round%22/%3E%3C/svg%3E')}\
.brand .logo{display:inline-block;width:24px;height:24px;border-radius:7px;background:#070b14 var(--logo) center/62% no-repeat;box-shadow:0 0 0 1px rgba(255,255,255,.14);overflow:hidden;flex:none}\
.brand .logo img{display:block;width:100%;height:100%;object-fit:contain}\
.brand:hover{color:#fff}\
h1{font-size:1.3rem;font-weight:600;letter-spacing:-.01em;margin:.2rem 0 .1rem}\
.nav{display:flex;flex-wrap:wrap;gap:.38rem;margin:.7rem 0 1.15rem}\
.nav a{font-size:.7rem;font-weight:500;letter-spacing:.05em;color:#98a1ae;padding:.42rem .78rem;border-radius:999px;border:1px solid rgba(255,255,255,.09);background:rgba(255,255,255,.035);transition:color .18s,border-color .18s,background .18s}\
.nav a:hover{color:#fff;border-color:rgba(127,169,255,.5);background:rgba(79,140,255,.14)}\
.nav a.on{color:#dce9ff;border-color:rgba(79,140,255,.55);background:rgba(79,140,255,.17)}\
h2{font-size:.68rem;font-weight:600;letter-spacing:.16em;text-transform:uppercase;color:#8b93a1;margin-bottom:.9rem}\
.glass{background:linear-gradient(165deg,rgba(255,255,255,.055),rgba(255,255,255,.018));border:1px solid rgba(255,255,255,.09);border-radius:18px;padding:1.2rem 1.2rem 1.3rem;backdrop-filter:blur(18px) saturate(150%);-webkit-backdrop-filter:blur(18px) saturate(150%);box-shadow:0 12px 40px rgba(0,0,0,.5),inset 0 1px 0 rgba(255,255,255,.05);margin-bottom:1rem;animation:rise .5s cubic-bezier(.2,.7,.3,1) both}\
@keyframes rise{from{opacity:0;transform:translateY(14px)}to{opacity:1;transform:none}}\
@keyframes spin{to{transform:rotate(360deg)}}\
table{width:100%;border-collapse:collapse}\
td{padding:.52rem .2rem;font-size:.86rem;color:#e4e8ee;border-bottom:1px solid rgba(255,255,255,.05);vertical-align:middle}\
tr:last-child td{border-bottom:none}\
td:first-child{color:#8b93a1;font-size:.67rem;letter-spacing:.1em;text-transform:uppercase;text-align:right;padding-right:.95rem;width:34%;white-space:nowrap}\
input[type=text],input[type=password]{width:100%;background:rgba(255,255,255,.05);border:1px solid rgba(255,255,255,.11);border-radius:10px;color:#fff;font-family:inherit;font-size:.88rem;padding:.6rem .7rem;transition:border-color .18s,box-shadow .18s,background .18s}\
input:focus{outline:none;border-color:rgba(79,140,255,.7);background:rgba(255,255,255,.07);box-shadow:0 0 0 3px rgba(79,140,255,.2)}\
input::placeholder{color:#5b6270}\
form{margin-bottom:.4rem}\
input[type=submit]{display:block;width:100%;margin-top:.7rem;padding:.68rem .9rem;border-radius:10px;border:1px solid rgba(79,140,255,.55);background:linear-gradient(180deg,#4f8cff,#3b74de);color:#fff;font-size:.85rem;font-weight:600;font-family:inherit;letter-spacing:.03em;cursor:pointer;box-shadow:0 6px 18px rgba(59,116,222,.28);transition:filter .15s,transform .1s}\
input[type=submit]:hover{filter:brightness(1.1)}\
input[type=submit]:active{transform:translateY(1px)}\
.nav-link{display:inline-block;padding:.45rem .95rem;background:rgba(255,255,255,.05);color:#c4cad3;border:1px solid rgba(255,255,255,.12);border-radius:999px;font-size:.74rem;font-weight:500;letter-spacing:.05em;margin:.3rem .2rem;transition:color .18s,border-color .18s,background .18s}\
.nav-link:hover{color:#fff;border-color:rgba(127,169,255,.5);background:rgba(79,140,255,.14)}\
a.home{display:inline-flex;align-items:center;gap:.5rem;color:#7d8694;font-size:.76rem;margin-bottom:.9rem}\
a.home:hover{color:#a9c8ff}\
.saved{text-align:center;padding:2.6rem 1.2rem 2.8rem;background:linear-gradient(165deg,rgba(255,255,255,.06),rgba(255,255,255,.02));border:1px solid rgba(255,255,255,.1);border-radius:18px;box-shadow:0 12px 40px rgba(0,0,0,.5);animation:rise .45s ease both}\
.saved-icon{width:56px;height:56px;margin:0 auto 1rem;border-radius:50%;display:flex;align-items:center;justify-content:center;background:rgba(79,140,255,.16);border:1px solid rgba(79,140,255,.5);color:#8ab4ff;font-size:1.5rem}\
.saved h3{font-size:.95rem;font-weight:600;color:#fff;margin:0 0 .45rem}\
.saved p{color:#98a1ae;font-size:.83rem;margin-bottom:1rem;line-height:1.5}\
.saved-cd{font-size:.72rem;color:#6f7684;letter-spacing:.05em}\
.saved-cd b{color:#cfe0ff;font-size:.95rem}\
.spin{width:42px;height:42px;margin:0 auto 1.1rem;border-radius:50%;border:3px solid rgba(255,255,255,.1);border-top-color:#4f8cff;animation:spin .8s linear infinite}\
@media(max-width:560px){\
body{padding:.9rem .75rem calc(1.2rem + env(safe-area-inset-bottom))}\
.glass{padding:1rem .95rem 1.05rem;border-radius:16px}\
td:first-child{white-space:normal;width:36%;font-size:.62rem}\
h1{font-size:1.15rem}\
}\
@media(prefers-reduced-motion:reduce){*{animation-duration:.01ms!important;animation-iteration-count:1!important;transition-duration:.01ms!important}}\
::-webkit-scrollbar{width:10px;height:10px}\
::-webkit-scrollbar-thumb{background:rgba(255,255,255,.14);border-radius:8px}\
::-webkit-scrollbar-track{background:transparent}\
</style>\
<script>window.addEventListener('error',function(e){if(e.target&&e.target.tagName=='IMG'){e.target.style.display='none';}},true);</script>\
</head>\
<body>\
<div id='wrap'>\
<div class='topbar'><a class='brand' href='/'><span class='logo'><img src='/favicon.png' alt=''></span><span>AeroLink</span></a></div>\
<h1>Setup</h1>\
<nav class='nav' aria-label='Sections'>\
<a href='/'>Home</a>\
<a href='/setup' class='on'>Setup</a>\
<a href='/scan'>Scan</a>\
<a href='/config'>Config</a>\
<a href='/mappings'>Mappings</a>\
<a href='/firewall'>Firewall</a>\
</nav>\
<script>\
var q=window.location.search.substring(1);\
if(q.indexOf('ap_ssid=')!==-1||(q.indexOf('ssid=')!==-1&&q.indexOf('password=')!==-1)){\
document.getElementById('wrap').innerHTML='<div class=saved><div class=spin></div><div class=saved-icon>&#10003;</div><h3>Setup saved</h3><p>Applying your network settings and rebooting.</p><div class=saved-cd>Reconnecting in <b id=cd>12</b> seconds</div></div>';\
var n=12;var cd=document.getElementById('cd');\
setInterval(function(){n--;if(cd)cd.textContent=n>0?n:0;},1000);\
var tries=0;\
function ping(){tries++;fetch('/',{cache:'no-store'}).then(function(r){if(r.ok){location.href='/';}else if(tries<90){setTimeout(ping,2000);}}).catch(function(){if(tries<90){setTimeout(ping,2000);}});}\
setTimeout(ping,4000);\
}\
</script>"

/* Setup form */
#define SETUP_CHUNK_FORM "\
<div class='glass'>\
<h2>Access Point</h2>\
<form action='/setup' method='GET'>\
<table>\
<tr><td>SSID</td><td><input type='text' name='ap_ssid' value='%s'/></td></tr>\
<tr><td>Password</td><td><input type='password' name='ap_password'/></td></tr>\
</table>\
<h2>Uplink</h2>\
<table>\
<tr><td>SSID</td><td><input type='text' name='ssid' value='%s'/></td></tr>\
<tr><td>Password</td><td><input type='password' name='password'/></td></tr>\
<tr><td></td><td><input type='submit' value='Save & Reboot' class='ok-btn'/></td></tr>\
</table></form></div>\
<div style='text-align:center;margin-top:1rem;'>\
<a href='/scan' class='nav-link'>📡 Scan</a>\
<a href='/' class='nav-link'>← Home</a>\
</div></div></body></html>"
#endif /* !CONFIG_ETH_UPLINK */
