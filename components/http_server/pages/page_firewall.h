/* Firewall page templates */
#include "router_config.h"

/* Nav pills that only exist on Wi-Fi builds. */
#if !CONFIG_ETH_UPLINK
#define FIREWALL_NAV_EXTRA "<a href='/setup'>Setup</a><a href='/scan'>Scan</a>"
#else
#define FIREWALL_NAV_EXTRA ""
#endif

/* Firewall Page - Chunked for streaming.
 * NOTE: every FIREWALL_CHUNK_* is streamed verbatim (no snprintf), so a
 * single literal % is correct here - never double it. */
#define FIREWALL_CHUNK_HEAD "<!doctype html>\
<html lang='en'>\
<head>\
<meta charset='utf-8'>\
<meta name='viewport' content='width=device-width,initial-scale=1'>\
<meta name='color-scheme' content='dark'>\
<meta name='theme-color' content='#000000'>\
<title>AeroLink - Firewall</title>\
<link rel='icon' href='/favicon.png'>\
<link href='https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&display=swap' rel='stylesheet'>\
<style>\
*{box-sizing:border-box;margin:0;padding:0}\
html{-webkit-text-size-adjust:100%}\
body{font-family:'Inter',system-ui,-apple-system,'Segoe UI',Roboto,Helvetica,Arial,sans-serif;background:#000;color:#eef1f6;color-scheme:dark;min-height:100vh;display:flex;flex-direction:column;align-items:center;padding:1.1rem 1rem calc(1.5rem + env(safe-area-inset-bottom))}\
body::before{content:'';position:fixed;inset:0;z-index:0;pointer-events:none;background:radial-gradient(700px 340px at 50% -120px,rgba(79,140,255,.22),transparent 70%),radial-gradient(520px 420px at 110% 110%,rgba(79,140,255,.07),transparent 70%)}\
#wrap{position:relative;z-index:1;width:100%;max-width:840px;margin:auto}\
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
.lede{color:#7b8391;font-size:.78rem;line-height:1.55;margin:-.7rem 0 1.1rem;letter-spacing:.02em}\
h2{font-size:.68rem;font-weight:600;letter-spacing:.16em;text-transform:uppercase;color:#8b93a1;margin-bottom:.9rem}\
.glass{background:linear-gradient(165deg,rgba(255,255,255,.055),rgba(255,255,255,.018));border:1px solid rgba(255,255,255,.09);border-radius:18px;padding:1.2rem 1.2rem 1.3rem;backdrop-filter:blur(18px) saturate(150%);-webkit-backdrop-filter:blur(18px) saturate(150%);box-shadow:0 12px 40px rgba(0,0,0,.5),inset 0 1px 0 rgba(255,255,255,.05);margin-bottom:1rem;overflow-x:auto;animation:rise .5s cubic-bezier(.2,.7,.3,1) both}\
@keyframes rise{from{opacity:0;transform:translateY(14px)}to{opacity:1;transform:none}}\
@keyframes pop{from{opacity:0;transform:scale(.94)}to{opacity:1;transform:none}}\
@keyframes fade{from{opacity:0}to{opacity:1}}\
.acl-section{margin-bottom:1rem;padding:.9rem .85rem .35rem;background:rgba(255,255,255,.02);border:1px solid rgba(255,255,255,.06);border-radius:14px}\
.acl-section h3{font-size:.7rem;font-weight:600;letter-spacing:.14em;text-transform:uppercase;color:#c3cad5;margin-bottom:.5rem}\
.stats{display:flex;flex-wrap:wrap;align-items:center;gap:.75rem;font-size:.66rem;letter-spacing:.05em;color:#7b8391;margin-bottom:.65rem}\
.stats .allowed{color:#5fd3a4}\
.stats .denied{color:#ff8f8f}\
.stats .orange-button{margin-left:auto}\
.data-table{width:100%;border-collapse:collapse}\
.data-table th{font-size:.6rem;font-weight:600;letter-spacing:.12em;text-transform:uppercase;color:#7b8391;text-align:left;padding:.5rem .45rem;border-bottom:1px solid rgba(255,255,255,.09);white-space:nowrap}\
.data-table td{padding:.5rem .45rem;font-size:.74rem;color:#cfd5de;border-bottom:1px solid rgba(255,255,255,.05);white-space:nowrap;max-width:150px;overflow:hidden;text-overflow:ellipsis;vertical-align:middle}\
.data-table tbody tr:last-child td{border-bottom:none}\
.data-table tbody tr:hover td{background:rgba(255,255,255,.03)}\
.data-table td[colspan]{text-align:center!important;color:#7b8391!important;max-width:none;white-space:normal}\
table{width:100%;border-collapse:collapse}\
table:not(.data-table) td{padding:.5rem .2rem;font-size:.86rem;color:#e4e8ee;border-bottom:1px solid rgba(255,255,255,.05);vertical-align:middle}\
table:not(.data-table) tr:last-child td{border-bottom:none}\
table:not(.data-table) td:first-child{color:#8b93a1;font-size:.67rem;letter-spacing:.1em;text-transform:uppercase;text-align:right;padding-right:.95rem;width:24%;white-space:nowrap}\
input[type=text],input[type=number],select{width:100%;background:rgba(255,255,255,.05);border:1px solid rgba(255,255,255,.11);border-radius:10px;color:#fff;font-family:inherit;font-size:.88rem;padding:.6rem .7rem;transition:border-color .18s,box-shadow .18s,background .18s}\
input:focus,select:focus{outline:none;border-color:rgba(79,140,255,.7);background:rgba(255,255,255,.07);box-shadow:0 0 0 3px rgba(79,140,255,.2)}\
input::placeholder{color:#5b6270}\
select{-webkit-appearance:none;appearance:none;padding-right:1.9rem;background-image:url('data:image/svg+xml,%3Csvg xmlns=%22http://www.w3.org/2000/svg%22 width=%2212%22 height=%228%22 viewBox=%220 0 12 8%22%3E%3Cpath d=%22M1 1.5l5 5 5-5%22 fill=%22none%22 stroke=%22%238b93a1%22 stroke-width=%221.6%22 stroke-linecap=%22round%22 stroke-linejoin=%22round%22/%3E%3C/svg%3E');background-repeat:no-repeat;background-position:right .75rem center;cursor:pointer}\
select option{background:#0a0c10;color:#fff}\
form{margin-bottom:.4rem}\
input[type=submit]{display:block;width:100%;margin-top:.6rem;padding:.66rem .9rem;border-radius:10px;border:1px solid rgba(79,140,255,.55);background:linear-gradient(180deg,#4f8cff,#3b74de);color:#fff;font-size:.85rem;font-weight:600;font-family:inherit;cursor:pointer;transition:filter .15s,transform .1s}\
input[type=submit]:hover{filter:brightness(1.1)}\
input[type=submit]:active{transform:translateY(1px)}\
.red-button,.orange-button{display:inline-block;padding:.26rem .58rem;border-radius:8px;font-size:.66rem;font-weight:600;letter-spacing:.04em;border:1px solid transparent;transition:background .18s,border-color .18s,color .18s}\
.red-button{background:rgba(255,70,70,.1);border-color:rgba(255,95,95,.28);color:#ff8f8f}\
.red-button:hover{background:rgba(255,70,70,.22);border-color:rgba(255,95,95,.55);color:#ffc0c0}\
.orange-button{background:rgba(255,255,255,.05);border-color:rgba(255,255,255,.14);color:#c4cad3}\
.orange-button:hover{background:rgba(255,255,255,.11);color:#fff}\
a[href*='logout']{position:absolute!important;top:.1rem;right:0;padding:.45rem .95rem!important;border-radius:999px!important;background:rgba(255,255,255,.05)!important;border:1px solid rgba(255,255,255,.14)!important;color:#c4cad3!important;font-size:.68rem!important;font-weight:600!important;font-family:inherit!important;letter-spacing:.12em;text-transform:uppercase;text-decoration:none!important;transition:all .18s!important}\
a[href*='logout']:hover{color:#fff!important;background:rgba(255,84,84,.14)!important;border-color:rgba(255,120,120,.5)!important}\
.modal-overlay{display:none;position:fixed;inset:0;z-index:1000;align-items:center;justify-content:center;padding:1.2rem;background:rgba(0,0,0,.66);backdrop-filter:blur(7px);-webkit-backdrop-filter:blur(7px)}\
.modal-overlay.show{display:flex;animation:fade .2s ease both}\
.modal-box{width:100%;max-width:330px;padding:1.5rem 1.3rem 1.35rem;border-radius:18px;text-align:center;background:linear-gradient(165deg,rgba(38,40,47,.96),rgba(14,15,18,.97));border:1px solid rgba(255,255,255,.12);box-shadow:0 30px 70px rgba(0,0,0,.75);animation:pop .22s cubic-bezier(.2,.8,.3,1.2) both}\
.modal-box h3{font-size:.72rem;font-weight:600;letter-spacing:.18em;text-transform:uppercase;color:#ff9d9d;margin-bottom:.6rem}\
.modal-box p{font-size:.85rem;line-height:1.55;color:#c3c9d3;margin-bottom:1.1rem}\
.modal-box button{width:100%;padding:.62rem;border-radius:10px;border:1px solid rgba(255,255,255,.16);background:rgba(255,255,255,.07);color:#fff;font-size:.85rem;font-weight:600;font-family:inherit;cursor:pointer;transition:background .18s}\
.modal-box button:hover{background:rgba(255,255,255,.13)}\
@media(max-width:720px){\
body{padding:.9rem .75rem calc(1.2rem + env(safe-area-inset-bottom))}\
.glass{padding:1rem .95rem 1.05rem;border-radius:16px}\
h1{font-size:1.15rem}\
table:not(.data-table) td:first-child{white-space:normal;width:30%;font-size:.62rem}\
.data-table{min-width:660px}\
}\
@media(prefers-reduced-motion:reduce){*{animation-duration:.01ms!important;animation-iteration-count:1!important;transition-duration:.01ms!important}}\
::-webkit-scrollbar{width:10px;height:10px}\
::-webkit-scrollbar-thumb{background:rgba(255,255,255,.14);border-radius:8px}\
::-webkit-scrollbar-track{background:transparent}\
</style>\
<script>window.addEventListener('error',function(e){if(e.target&&e.target.tagName=='IMG'){e.target.style.display='none';}},true);</script>\
</head>\
<body>\
<script>\
document.addEventListener('click',function(e){\
var a=e.target&&e.target.closest?e.target.closest('a'):null;\
if(!a){return;}\
if(a.classList.contains('red-button')){if(!confirm('Delete this rule?')){e.preventDefault();}}\
else if(a.classList.contains('orange-button')){if(!confirm('Clear these counters?')){e.preventDefault();}}\
});\
</script>"
#define FIREWALL_CHUNK_MID1 "\
<div id='wrap'>\
<div class='topbar'><a class='brand' href='/'><span class='logo'><img src='/favicon.png' alt=''></span><span>AeroLink</span></a></div>\
<h1>Firewall</h1>\
<nav class='nav' aria-label='Sections'>\
<a href='/'>Home</a>" FIREWALL_NAV_EXTRA "\
<a href='/config'>Config</a>\
<a href='/mappings'>Mappings</a>\
<a href='/firewall' class='on'>Firewall</a>\
</nav>"
#define FIREWALL_CHUNK_MID2 "\
<p class='lede'>Rules evaluate top to bottom - the first match wins. Keep at least one allow rule for the interface you manage the device from.</p>"
#define FIREWALL_CHUNK_TAIL "\
<div class='glass'>\
<h2>Add Rule</h2>\
<form action='/firewall' method='GET'>\
<table class='ftbl'>\
<tr><td>Dir</td><td><select name='acl_list'><option value='0'>To ESP</option><option value='1'>From ESP</option><option value='2'>To AP</option><option value='3'>From AP</option></select></td></tr>\
<tr><td>Proto</td><td><select name='proto'><option value='0'>IP</option><option value='6'>TCP</option><option value='17'>UDP</option><option value='1'>ICMP</option></select></td></tr>\
<tr><td>SRC IP</td><td><input type='text' name='src_ip' placeholder='any or device name'/></td></tr>\
<tr><td>SRC Port</td><td><input type='text' name='src_port' placeholder='*'/></td></tr>\
<tr><td>DST IP</td><td><input type='text' name='dst_ip' placeholder='any or device name'/></td></tr>\
<tr><td>DST Port</td><td><input type='text' name='dst_port' placeholder='*'/></td></tr>\
<tr><td>Action</td><td><select name='action'><option value='1'>Allow</option><option value='0'>Deny</option><option value='3'>Allow+Mon</option><option value='2'>Deny+Mon</option></select></td></tr>\
<tr><td></td><td><input type='submit' name='acl_action' value='Add Rule' class='ok-btn'/></td></tr>\
</table></form></div>\
</div></body></html>"
