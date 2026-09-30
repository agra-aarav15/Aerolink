/* Configuration page templates */
#include "router_config.h"
#include "wifi_config.h"

/* Nav pills that only exist on Wi-Fi builds (setup + scan have no handler
 * when CONFIG_ETH_UPLINK, so they must never be linked there). */
#if !CONFIG_ETH_UPLINK
#define CONFIG_NAV_EXTRA "<a href='/setup'>Setup</a><a href='/scan'>Scan</a>"
#else
#define CONFIG_NAV_EXTRA ""
#endif

/* Configuration Page - WiFi settings and MAC addresses.
 * Config Page - Chunked for streaming.
 * NOTE: CONFIG_CHUNK_HEAD / _SCRIPT / _TAIL / _TAIL2 are streamed verbatim
 * (no snprintf), so literal % is fine there. The CONFIG_CHUNK_AP / _STA /
 * _STATIC / _RC / _PCAP sections ARE printf-formatted into a fixed buffer
 * below - keep them small and double any literal % as %%. */
#define CONFIG_CHUNK_HEAD "<!doctype html>\
<html lang='en'>\
<head>\
<meta charset='utf-8'>\
<meta name='viewport' content='width=device-width,initial-scale=1'>\
<meta name='color-scheme' content='dark'>\
<meta name='theme-color' content='#000000'>\
<title>AeroLink - Config</title>\
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
.glass{background:linear-gradient(165deg,rgba(255,255,255,.055),rgba(255,255,255,.018));border:1px solid rgba(255,255,255,.09);border-radius:18px;padding:1.2rem 1.2rem 1.3rem;backdrop-filter:blur(18px) saturate(150%);-webkit-backdrop-filter:blur(18px) saturate(150%);box-shadow:0 12px 40px rgba(0,0,0,.5),inset 0 1px 0 rgba(255,255,255,.05);margin-bottom:.95rem;animation:rise .5s cubic-bezier(.2,.7,.3,1) both}\
@keyframes rise{from{opacity:0;transform:translateY(14px)}to{opacity:1;transform:none}}\
@keyframes pop{from{opacity:0;transform:scale(.94)}to{opacity:1;transform:none}}\
@keyframes spin{to{transform:rotate(360deg)}}\
table{width:100%;border-collapse:collapse}\
td{padding:.52rem .2rem;font-size:.86rem;color:#e4e8ee;border-bottom:1px solid rgba(255,255,255,.05);vertical-align:middle}\
tr:last-child td{border-bottom:none}\
td:first-child{color:#8b93a1;font-size:.67rem;letter-spacing:.1em;text-transform:uppercase;text-align:right;padding-right:.95rem;width:34%;white-space:nowrap}\
td[colspan]{text-align:left!important;white-space:normal!important;color:#5f6672!important;letter-spacing:.12em;font-size:.64rem!important;padding-top:.75rem;border-bottom:none}\
input[type=text],input[type=password],input[type=number],select{width:100%;background:rgba(255,255,255,.05);border:1px solid rgba(255,255,255,.11);border-radius:10px;color:#fff;font-family:inherit;font-size:.88rem;padding:.6rem .7rem;transition:border-color .18s,box-shadow .18s,background .18s}\
input:focus,select:focus{outline:none;border-color:rgba(79,140,255,.7);background:rgba(255,255,255,.07);box-shadow:0 0 0 3px rgba(79,140,255,.2)}\
input::placeholder{color:#5b6270}\
select{-webkit-appearance:none;appearance:none;padding-right:1.9rem;background-image:url('data:image/svg+xml,%3Csvg xmlns=%22http://www.w3.org/2000/svg%22 width=%2212%22 height=%228%22 viewBox=%220 0 12 8%22%3E%3Cpath d=%22M1 1.5l5 5 5-5%22 fill=%22none%22 stroke=%22%238b93a1%22 stroke-width=%221.6%22 stroke-linecap=%22round%22 stroke-linejoin=%22round%22/%3E%3C/svg%3E');background-repeat:no-repeat;background-position:right .75rem center;cursor:pointer}\
select option{background:#0a0c10;color:#fff}\
input[type=checkbox],input[type=radio]{-webkit-appearance:none;appearance:none;width:17px;height:17px;border:1px solid rgba(255,255,255,.25);background:rgba(255,255,255,.05);border-radius:5px;cursor:pointer;vertical-align:middle;position:relative;transition:.15s}\
input[type=radio]{border-radius:50%}\
input[type=checkbox]:hover,input[type=radio]:hover{border-color:rgba(127,169,255,.7)}\
input:checked{background:#4f8cff;border-color:#4f8cff}\
input[type=checkbox]:checked::after{content:'';position:absolute;left:5px;top:1.5px;width:4px;height:8px;border:solid #fff;border-width:0 2px 2px 0;transform:rotate(45deg)}\
input[type=radio]:checked::after{content:'';position:absolute;left:4.5px;top:4.5px;width:5px;height:5px;border-radius:50%;background:#fff}\
label{font-size:.78rem;color:#b6bdc8;cursor:pointer}\
small{color:#6f7684;font-size:.7rem;line-height:1.45}\
td small{display:inline-block;margin-left:.45rem;text-transform:uppercase;letter-spacing:.06em;font-size:.63rem;vertical-align:middle;color:#7b8391}\
form>small{display:block;margin-top:.55rem}\
form{margin-bottom:.4rem}\
.ok-btn{display:block;width:100%;margin-top:.65rem;padding:.68rem .9rem;border-radius:10px;border:1px solid rgba(79,140,255,.55);background:linear-gradient(180deg,#4f8cff,#3b74de);color:#fff;font-size:.85rem;font-weight:600;font-family:inherit;letter-spacing:.03em;cursor:pointer;box-shadow:0 6px 18px rgba(59,116,222,.28);transition:filter .15s,transform .1s}\
.ok-btn:hover{filter:brightness(1.1)}\
.ok-btn:active{transform:translateY(1px)}\
input[type=submit].red-btn,.red-btn{display:block;width:100%;margin-top:.65rem;padding:.68rem .9rem;border-radius:10px;border:1px solid rgba(255,95,95,.4);background:rgba(255,70,70,.12);color:#ff8f8f;font-size:.85rem;font-weight:600;font-family:inherit;cursor:pointer;transition:background .15s,border-color .15s,color .15s}\
input[type=submit].red-btn:hover,.red-btn:hover{background:rgba(255,70,70,.22);border-color:rgba(255,95,95,.65);color:#ffc0c0}\
input[type=submit]{display:block;width:100%;margin-top:.65rem;padding:.68rem .9rem;border-radius:10px;border:1px solid rgba(79,140,255,.55);background:linear-gradient(180deg,#4f8cff,#3b74de);color:#fff;font-size:.85rem;font-weight:600;font-family:inherit;cursor:pointer;transition:filter .15s}\
input[type=submit]:hover{filter:brightness(1.1)}\
a[href*='logout']{position:absolute!important;top:.1rem;right:0;padding:.45rem .95rem!important;border-radius:999px!important;background:rgba(255,255,255,.05)!important;border:1px solid rgba(255,255,255,.14)!important;color:#c4cad3!important;font-size:.68rem!important;font-weight:600!important;font-family:inherit!important;letter-spacing:.12em;text-transform:uppercase;text-decoration:none!important;transition:all .18s!important}\
a[href*='logout']:hover{color:#fff!important;background:rgba(255,84,84,.14)!important;border-color:rgba(255,120,120,.5)!important}\
.glass h3{font-size:.67rem;font-weight:600;letter-spacing:.14em;text-transform:uppercase;color:#aab2bf;margin:1.15rem 0 .6rem;padding-top:.95rem;border-top:1px solid rgba(255,255,255,.07)}\
.glass h3:first-of-type{margin-top:.4rem;padding-top:0;border-top:none}\
input[type=file]{display:none}\
.file{display:block;width:100%;padding:.7rem .9rem;border:1px dashed rgba(255,255,255,.2);border-radius:10px;background:rgba(255,255,255,.03);color:#98a1ae;font-size:.78rem;text-align:center;cursor:pointer;transition:border-color .18s,color .18s,background .18s;letter-spacing:.03em}\
.file:hover{border-color:rgba(127,169,255,.6);color:#fff;background:rgba(79,140,255,.08)}\
#otaBar{display:none;height:6px;background:rgba(255,255,255,.08);border-radius:999px;margin-top:.75rem;overflow:hidden}\
#otaBarFill{height:100%;width:0;background:linear-gradient(90deg,#4f8cff,#8ab4ff);border-radius:999px;transition:width .25s ease}\
#otaStatus,#exportStatus,#importStatus{margin-top:.55rem;font-size:.76rem;color:#8b93a1;letter-spacing:.03em;min-height:1em}\
#expPass,#impPass{margin-bottom:.55rem}\
#rebootScreen{display:none}\
.saved{text-align:center;padding:2.6rem 1.2rem 2.8rem;background:linear-gradient(165deg,rgba(255,255,255,.06),rgba(255,255,255,.02));border:1px solid rgba(255,255,255,.1);border-radius:18px;box-shadow:0 12px 40px rgba(0,0,0,.5);animation:rise .45s ease both}\
.saved-icon{width:56px;height:56px;margin:0 auto 1rem;border-radius:50%;display:flex;align-items:center;justify-content:center;background:rgba(79,140,255,.16);border:1px solid rgba(79,140,255,.5);color:#8ab4ff;font-size:1.5rem}\
.saved h3{font-size:.95rem;font-weight:600;letter-spacing:.02em;text-transform:none;color:#fff;margin:0 0 .45rem;padding:0;border:none}\
.saved p{color:#98a1ae;font-size:.83rem;margin-bottom:1rem;line-height:1.5}\
.saved-cd{font-size:.72rem;color:#6f7684;letter-spacing:.05em}\
.saved-cd b{color:#cfe0ff;font-size:.95rem}\
.spin{width:42px;height:42px;margin:0 auto 1.1rem;border-radius:50%;border:3px solid rgba(255,255,255,.1);border-top-color:#4f8cff;animation:spin .8s linear infinite}\
#wrap.rebooting>*{display:none}\
#wrap.rebooting>#rebootScreen{display:block}\
.back{text-align:center;margin-top:1.4rem}\
.back a{color:#7d8694;font-size:.78rem;letter-spacing:.04em;border-bottom:1px solid rgba(255,255,255,.15);padding-bottom:1px}\
.back a:hover{color:#a9c8ff;border-color:rgba(127,169,255,.6)}\
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
<h1>Configuration</h1>\
<nav class='nav' aria-label='Sections'>\
<a href='/'>Home</a>" CONFIG_NAV_EXTRA "\
<a href='/config' class='on'>Config</a>\
<a href='/mappings'>Mappings</a>\
<a href='/firewall'>Firewall</a>\
</nav>"
/* After logout section */
#define CONFIG_CHUNK_SCRIPT "\
<script>\
var q=window.location.search.substring(1);\
if(q.indexOf('ap_ssid=')!==-1||(q.indexOf('ssid=')!==-1&&q.indexOf('password=')!==-1)||q.indexOf('staticip=')!==-1||q.indexOf('reset=')!==-1||q.indexOf('disable_interface=')!==-1){\
var w=document.getElementById('wrap');\
w.innerHTML='<div class=saved><div class=saved-icon>&#10003;</div><h3>Settings saved</h3><p>Applying changes and rebooting the device.</p><div class=saved-cd>Reconnecting in <b id=cd>12</b> seconds</div></div>';\
var n=12;var cd=document.getElementById('cd');\
setInterval(function(){n--;if(cd)cd.textContent=n>0?n:0;},1000);\
var tries=0;\
function ping(){tries++;fetch('/',{cache:'no-store'}).then(function(r){if(r.ok){location.href='/';}else if(tries<90){setTimeout(ping,2000);}}).catch(function(){if(tries<90){setTimeout(ping,2000);}});}\
setTimeout(ping,4000);\
}\
</script>"

/* AP Settings section */
#if CONFIG_ETH_UPLINK
#define CONFIG_CHUNK_AP_CHANNEL_ROW \
"<tr><td>Channel</td><td><input type='number' name='ap_channel' min='0' max='13' value='%d' style='width:4em'/> <small>0=auto</small></td></tr>"
#else
#define CONFIG_CHUNK_AP_CHANNEL_ROW ""
#endif
#define CONFIG_CHUNK_AP "\
<div class='glass'>\
<h2>Access Point</h2>\
<form action='' method='GET'>\
<table>\
<tr><td>SSID</td><td><input type='text' name='ap_ssid' value='%s'/></td></tr>\
<tr><td>Password</td><td><input type='password' id='ap_pw' name='ap_password' oninput=\"document.getElementById('ap_op').checked=false;\"/></td></tr>\
<tr><td>AP IP</td><td><input type='text' name='ap_ip_addr' value='%s'/></td></tr>\
<tr><td>Hostname</td><td><input type='text' name='ap_hostname' value='%s' maxlength='32'/></td></tr>\
<tr><td>DNS</td><td><input type='text' name='ap_dns' value='%s'/></td></tr>\
<tr><td>MAC</td><td><input type='text' name='ap_mac' value='%s'/></td></tr>\
" CONFIG_CHUNK_AP_CHANNEL_ROW "\
<tr><td>Security</td><td><select name='ap_auth'><option value='0' %s>WPA2/WPA3</option><option value='1' %s>WPA2</option><option value='2' %s>WPA3</option></select></td></tr>\
<tr><td>NAT</td><td><input type='checkbox' name='ap_nat' value='1' %s> <small>Enabled</small></td></tr>\
<tr><td>Enabled</td><td><input type='checkbox' name='ap_enabled' value='1' %s></td></tr>\
<tr><td>Options</td><td><input type='checkbox' id='ap_op' name='ap_open' value='1' %s onchange=\"if(this.checked)document.getElementById('ap_pw').value='';\"> <small>Open</small> &nbsp; <input type='checkbox' name='ap_hidden' value='1' %s> <small>Hidden</small></td></tr>\
<tr><td></td><td><input type='submit' value='Save & Reboot' class='ok-btn'/></td></tr>\
</table></form></div>"

#if !CONFIG_ETH_UPLINK
#if WIFI_HAS_5GHZ
#define CONFIG_CHUNK_STA_BAND_ROW \
"<tr><td>Band</td><td><select name='sta_band'><option value='0' %s>Auto</option><option value='1' %s>2.4GHz</option><option value='2' %s>5GHz</option></select></td></tr>"
#else
#define CONFIG_CHUNK_STA_BAND_ROW ""
#endif

#define CONFIG_CHUNK_STA "\
<div class='glass'>\
<h2>Station (Uplink)</h2>\
<form action='' method='GET'>\
<table>\
<tr><td>SSID</td><td><input type='text' name='ssid' value='%s'/></td></tr>\
<tr><td>Password</td><td><input type='password' name='password'/></td></tr>\
" CONFIG_CHUNK_STA_BAND_ROW "\
<tr><td colspan='2'>WPA2 Enterprise</td></tr>\
<tr><td>Username</td><td><input type='text' name='ent_username' value='%s'/></td></tr>\
<tr><td>Identity</td><td><input type='text' name='ent_identity' value='%s'/></td></tr>\
<tr><td>EAP</td><td><select name='eap_method'><option value='0' %s>Auto</option><option value='1' %s>PEAP</option><option value='2' %s>TTLS</option><option value='3' %s>TLS</option></select></td></tr>\
<tr><td>TTLS P2</td><td><select name='ttls_phase2'><option value='0' %s>MSCHAPv2</option><option value='1' %s>MSCHAP</option><option value='2' %s>PAP</option><option value='3' %s>CHAP</option></select></td></tr>\
<tr><td>Cert</td><td><input type='checkbox' name='cert_bundle' value='1' %s> <small>CA bundle</small> &nbsp; <input type='checkbox' name='no_time_chk' value='1' %s> <small>Skip check</small></td></tr>\
<tr><td>MAC</td><td><input type='text' name='sta_mac' value='%s'/></td></tr>\
<tr><td></td><td><input type='submit' value='Save & Reboot' class='ok-btn'/></td></tr>\
</table></form></div>"
#endif

/* Static IP */
#define CONFIG_CHUNK_STATIC "\
<div class='glass'>\
<h2>Static IP</h2>\
<form action='' method='GET'>\
<table>\
<tr><td>IP</td><td><input type='text' name='staticip' value='%s'/></td></tr>\
<tr><td>Subnet</td><td><input type='text' name='subnetmask' value='%s'/></td></tr>\
<tr><td>Gateway</td><td><input type='text' name='gateway' value='%s'/></td></tr>\
<tr><td></td><td><input type='submit' value='Save & Reboot' class='ok-btn'/></td></tr>\
</table><small>Leave empty for DHCP</small></form></div>"

/* Remote Console */
#define CONFIG_CHUNK_RC "\
<div class='glass'>\
<h2>Remote Console</h2>\
<form action='' method='GET'>\
<input type='hidden' name='rc_save' value='1'/>\
<table>\
<tr><td>Service</td><td><label style='margin-right:0.8rem;'><input type='radio' name='rc_enabled' value='1' %s> On</label><label><input type='radio' name='rc_enabled' value='0' %s> Off</label></td></tr>\
<tr><td>Status</td><td><span style='color:%s;font-size:0.8rem;'>%s</span>%s</td></tr>\
<tr><td>Port</td><td><input type='number' name='rc_port' value='%d' min='1' max='65535' style='width:80px;'/></td></tr>\
<tr><td>Bind</td><td><label style='margin-right:0.6rem;'><input type='checkbox' name='rc_bind_ap' value='1' %s> AP</label><label><input type='checkbox' name='rc_bind_sta' value='1' %s> STA</label></td></tr>\
<tr><td>Timeout</td><td><input type='number' name='rc_timeout' value='%lu' min='0' max='86400' style='width:80px;'/> <small>sec</small></td></tr>\
<tr><td></td><td><input type='submit' value='Save' class='ok-btn'/></td></tr>\
</table></form></div>"

/* PCAP */
#define CONFIG_CHUNK_PCAP "\
<div class='glass'>\
<h2>Packet Capture</h2>\
<form action='' method='GET'>\
<input type='hidden' name='pcap_save' value='1'/>\
<table>\
<tr><td>Mode</td><td><select name='pcap_mode'><option value='off' %s>Off</option><option value='acl' %s>ACL</option><option value='promisc' %s>Promiscuous</option></select></td></tr>\
<tr><td>Client</td><td><span style='color:%s;font-size:0.8rem;'>%s</span></td></tr>\
<tr><td>Stats</td><td style='font-size:0.8rem;color:#8b93a1;'>%lu cap, %lu drop</td></tr>\
<tr><td>Snaplen</td><td><input type='text' name='pcap_snaplen' value='%d'/></td></tr>\
<tr><td></td><td><input type='submit' value='Save' class='ok-btn'/></td></tr>\
</table><small>nc %s 19000 | wireshark -k -i -</small></form></div>"

/* Footer with OTA */
#define CONFIG_CHUNK_TAIL "\
<div class='glass'>\
<h2>Device</h2>"
#define CONFIG_CHUNK_TAIL2 "\
<h3>OTA Update</h3>\
<div class='file' onclick=\"document.getElementById('otaFile').click()\"><span id='otaFileName'>Choose .bin firmware file</span></div>\
<input type='file' id='otaFile' accept='.bin'/>\
<button type='button' onclick='uploadOTA()' class='ok-btn'>Upload firmware</button>\
<div id='otaBar'><div id='otaBarFill'></div></div>\
<div id='otaStatus'></div>\
<h3>Backup</h3>\
<table>\
<tr><td>Export</td><td>\
<input type='password' id='expPass' placeholder='Passphrase'/>\
<button type='button' onclick='downloadConfig()' class='ok-btn'>Download config</button>\
<div id='exportStatus'></div></td></tr>\
<tr><td>Import</td><td>\
<input type='password' id='impPass' placeholder='Passphrase'/>\
<div class='file' onclick=\"document.getElementById('cfgFile').click()\"><span id='cfgFileName'>Choose .json backup file</span></div>\
<input type='file' id='cfgFile' accept='.json'/>\
<button type='button' onclick='uploadConfig()' class='ok-btn'>Restore config</button>\
<div id='importStatus'></div></td></tr>\
</table>\
<h3>Reboot</h3>\
<form action='' method='GET'>\
<table><tr><td></td><td><input type='submit' name='reset' value='Reboot' class='red-btn'/></td></tr></table>\
</form></div>\
<div id='rebootScreen'><div class='saved'><div class='spin'></div><h3>Rebooting</h3><p>Keep the device powered. It reconnects automatically.</p><div class='saved-cd'>Reconnecting in <b id='cd2'>--</b> seconds</div></div></div>\
<script>\
var otaFileEl=document.getElementById('otaFile');\
otaFileEl.addEventListener('change',function(){document.getElementById('otaFileName').textContent=this.files[0]?this.files[0].name:'Choose .bin firmware file';});\
var cfgFileEl=document.getElementById('cfgFile');\
cfgFileEl.addEventListener('change',function(){document.getElementById('cfgFileName').textContent=this.files[0]?this.files[0].name:'Choose .json backup file';});\
function aeroReboot(sec){\
var w=document.getElementById('wrap');\
w.className='rebooting';\
document.getElementById('rebootScreen').style.display='block';\
var n=sec;var el=document.getElementById('cd2');if(el)el.textContent=n;\
var t=setInterval(function(){n--;if(el)el.textContent=n>0?n:0;},1000);\
var tries=0;\
function ping(){tries++;fetch('/',{cache:'no-store'}).then(function(r){if(r.ok){clearInterval(t);location.href='/';}else if(tries<90){setTimeout(ping,2000);}}).catch(function(){if(tries<90){setTimeout(ping,2000);}});}\
setTimeout(ping,4000);\
}\
function uploadOTA(){\
var f=document.getElementById('otaFile').files[0];\
if(!f){document.getElementById('otaStatus').textContent='Choose a firmware file first';return;}\
document.getElementById('otaStatus').textContent='Uploading...';\
document.getElementById('otaBar').style.display='block';\
var xhr=new XMLHttpRequest();xhr.open('POST','/api/ota-upload',true);\
xhr.upload.onprogress=function(e){if(e.lengthComputable){var p=Math.round(e.loaded/e.total*100);document.getElementById('otaBarFill').style.width=p+'%';document.getElementById('otaStatus').textContent='Uploading '+p+'%';}};\
xhr.onload=function(){try{var d=JSON.parse(xhr.responseText);if(d.ok){aeroReboot(12);}else{document.getElementById('otaBarFill').style.width='0';document.getElementById('otaBar').style.display='none';document.getElementById('otaStatus').textContent=d.msg||'Upload failed';}}catch(e){document.getElementById('otaStatus').textContent='Upload error';}};\
xhr.onerror=function(){document.getElementById('otaStatus').textContent='Connection error';};xhr.send(f);}\
function downloadConfig(){\
var pass=document.getElementById('expPass').value;\
var st=document.getElementById('exportStatus');st.textContent='Preparing export...';\
fetch('/api/config-export',{method:'POST',body:JSON.stringify({pass:pass}),headers:{'Content-Type':'application/json'}}).then(function(r){if(!r.ok){throw new Error('fail');}\
var cd=r.headers.get('Content-Disposition')||'';var fn='config.json';var i=cd.indexOf('filename=');if(i>-1){fn=cd.substring(i+9).replace(/[\";]/g,'').trim();}\
return r.blob().then(function(b){return{b:b,fn:fn};});}).then(function(o){var url=URL.createObjectURL(o.b);var a=document.createElement('a');a.href=url;a.download=o.fn;document.body.appendChild(a);a.click();setTimeout(function(){URL.revokeObjectURL(url);a.remove();},100);st.textContent='Downloaded';}).catch(function(){st.textContent='Export failed - check the passphrase';});}\
function uploadConfig(){\
var f=document.getElementById('cfgFile').files[0];var pass=document.getElementById('impPass').value;var st=document.getElementById('importStatus');\
if(!f){st.textContent='Choose a backup file first';return;}\
var r=new FileReader();\
r.onload=function(){st.textContent='Restoring...';var h={'Content-Type':'application/json'};if(pass){h['X-Config-Pass']=pass;}\
fetch('/api/config-import',{method:'POST',body:r.result,headers:h}).then(function(res){return res.json();}).then(function(d){if(d.ok){aeroReboot(8);}else{st.textContent=d.msg||'Restore failed';}}).catch(function(){st.textContent='Connection error';});};\
r.readAsText(f);}\
</script>\
<div class='back'><a href='/'>Back to dashboard</a></div>\
</div></body></html>"

/* Danger Zone removed — VPN and web bind restrictions no longer shown */
