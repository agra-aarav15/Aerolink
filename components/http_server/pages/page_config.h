/* Configuration page templates */
#include "router_config.h"
#include "wifi_config.h"

/* Configuration Page - WiFi settings and MAC addresses */
/* Config Page - Chunked for streaming */
#define CONFIG_CHUNK_HEAD "<html>\
<head>\
<meta name='viewport' content='width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0'>\
<meta charset='UTF-8'>\
<title>AeroLink — Config</title>\
<link rel='icon' href='favicon.png'>\
<link href='https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600;700&display=swap' rel='stylesheet'>\
</head>\
<style>\
*{box-sizing:border-box;margin:0;padding:0;}\
body{font-family:'Inter',sans-serif;background:#000;color:#fff;padding:1.2rem;min-height:100vh;display:flex;justify-content:center;}\
#wrap{width:100%;max-width:520px;}\
h1{font-size:1.1rem;font-weight:300;color:#fff;letter-spacing:3px;text-transform:uppercase;margin-bottom:0.5rem;}\
h2{font-size:0.7rem;font-weight:600;color:#555;text-transform:uppercase;letter-spacing:2px;margin:1.2rem 0 0.6rem;border-bottom:1px solid rgba(255,255,255,0.05);padding-bottom:0.4rem;}\
.glass{background:rgba(255,255,255,0.04);backdrop-filter:blur(20px);-webkit-backdrop-filter:blur(20px);border:1px solid rgba(255,255,255,0.08);border-radius:16px;padding:1.2rem;margin-bottom:0.8rem;}\
a.home{display:inline-flex;align-items:center;gap:0.5rem;color:#555;text-decoration:none;font-size:0.75rem;margin-bottom:1rem;transition:color 0.3s;}\
a.home:hover{color:#aaa;}\
@keyframes fadeIn{from{opacity:0;transform:translateY(12px);}to{opacity:1;transform:translateY(0);}}\
.glass{animation:fadeIn 0.5s ease-out both;}\
.glass:nth-child(2){animation-delay:0.08s;}\
.glass:nth-child(3){animation-delay:0.16s;}\
.glass:nth-child(4){animation-delay:0.24s;}\
.ok-btn,.red-btn{transition:all 0.3s ease,box-shadow 0.3s;}\
.ok-btn:hover{box-shadow:0 0 12px rgba(255,255,255,0.1);}\
form{margin-bottom:0.5rem;}\
table{width:100%;border-collapse:collapse;}\
td{padding:0.4rem 0;vertical-align:top;}\
td:first-child{color:#555;font-size:0.75rem;padding-right:0.75rem;width:35%;text-align:right;text-transform:uppercase;letter-spacing:0.5px;}\
input[type='text'],input[type='password'],input[type='number']{width:100%%;max-width:100%;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:8px;color:#fff;padding:0.6rem;font-size:0.85rem;transition:all 0.3s;box-sizing:border-box;overflow:hidden;}\
input:focus{outline:none;border-color:rgba(255,255,255,0.2);background:rgba(255,255,255,0.06);}\
input::placeholder{color:#333;}\
select{width:100%%;max-width:100%;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:8px;color:#fff;padding:0.6rem;font-size:0.85rem;cursor:pointer;-webkit-appearance:none;box-sizing:border-box;overflow:hidden;background-image:url(\"data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='10' height='6'%3E%3Cpath d='M1 1l4 4 4-4' stroke='%23555' stroke-width='1.5' fill='none'/%3E%3C/svg%3E\");background-repeat:no-repeat;background-position:right 0.6rem center;padding-right:1.5rem;}\
select option{background:#111;color:#fff;}\
input[type='checkbox'],input[type='radio']{-webkit-appearance:none;appearance:none;width:16px;height:16px;border:1px solid rgba(255,255,255,0.15);border-radius:4px;background:rgba(255,255,255,0.04);cursor:pointer;vertical-align:middle;position:relative;}\
input[type='radio']{border-radius:50%%;}\
input:checked{background:#fff;border-color:#fff;}\
input[type='checkbox']:checked::after{content:'';position:absolute;left:4px;top:1px;width:5px;height:8px;border:solid #000;border-width:0 2px 2px 0;transform:rotate(45deg);}\
input[type='radio']:checked::after{content:'';position:absolute;left:4px;top:4px;width:6px;height:6px;border-radius:50%%;background:#000;}\
.ok-btn{background:rgba(255,255,255,0.08);color:#fff;border:1px solid rgba(255,255,255,0.1);border-radius:8px;padding:0.6rem;font-size:0.85rem;font-weight:500;cursor:pointer;width:100%%;margin-top:0.3rem;transition:all 0.3s;}\
.ok-btn:hover{background:rgba(255,255,255,0.14);}\
.red-btn{background:rgba(244,67,54,0.15);color:#f44336;border:1px solid rgba(244,67,54,0.2);border-radius:8px;padding:0.6rem;font-size:0.85rem;font-weight:500;cursor:pointer;width:100%%;margin-top:0.3rem;transition:all 0.3s;}\
.red-btn:hover{background:rgba(244,67,54,0.25);}\
small{display:block;color:#333;font-size:0.7rem;margin-top:0.3rem;line-height:1.3;}\
@media(max-width:600px){body{padding:1rem;}td:first-child{font-size:0.7rem;width:40%%;}}\
</style>\
<body>\
<div id='wrap'>\
<a href='/' class='home'>← Home</a>\
<h1>AeroLink — Config</h1>"
/* After logout section */
#define CONFIG_CHUNK_SCRIPT "\
<script>\
var qs=window.location.search.substr(1);\
if(qs.indexOf('ap_ssid=')!==-1||(qs.indexOf('ssid=')!==-1&&qs.indexOf('password=')!==-1)||qs.indexOf('staticip=')!==-1||qs.indexOf('reset=')!==-1||qs.indexOf('disable_interface=')!==-1){\
document.getElementById('wrap').innerHTML='<h1>AeroLink — Config</h1><div class=\"glass\"><p style=\"text-align:center;color:#888;\">Saved. Rebooting...</p></div>';\
setTimeout(\"location.href='/'\",8000);}\
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
<tr><td colspan='2' style='padding-top:0.5rem;color:#333;font-size:0.7rem;'>WPA2 Enterprise</td></tr>\
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
<tr><td>Stats</td><td style='font-size:0.8rem;color:#888;'>%lu cap, %lu drop</td></tr>\
<tr><td>Snaplen</td><td><input type='text' name='pcap_snaplen' value='%d'/></td></tr>\
<tr><td></td><td><input type='submit' value='Save' class='ok-btn'/></td></tr>\
</table><small>nc %s 19000 | wireshark -k -i -</small></form></div>"

/* Footer with OTA */
#define CONFIG_CHUNK_TAIL "\
<div class='glass'>\
<h2>Device</h2>\
<h3 style='font-size:0.75rem;color:#555;margin:0.5rem 0;'>OTA Update</h3>"
#define CONFIG_CHUNK_TAIL2 "\
<table>\
<tr><td>Upload</td><td>\
<label style='display:inline-block;padding:0.5rem 1rem;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:8px;color:#888;font-size:0.8rem;cursor:pointer;'>\
<input type='file' id='otaFile' accept='.bin' style='display:none;'/>\
<span id='otaFileName'>Choose .bin</span></label><br/>\
<button type='button' onclick='uploadOTA()' class='ok-btn'>Upload</button>\
<div id='otaBar' style='display:none;height:4px;background:rgba(255,255,255,0.05);border-radius:2px;margin-top:0.5rem;overflow:hidden;'>\
<div id='otaBarFill' style='height:100%%;width:0;background:#fff;transition:width 0.3s;'></div></div>\
<div id='otaStatus' style='margin-top:0.3rem;font-size:0.8rem;color:#888;'></div></td></tr></table>\
<h3 style='font-size:0.75rem;color:#555;margin:1rem 0 0.5rem;'>Backup</h3>\
<table>\
<tr><td>Export</td><td><input type='password' id='expPass' placeholder='Passphrase' style='width:100%%;margin-bottom:0.3rem;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:8px;color:#fff;padding:0.5rem;font-size:0.8rem;box-sizing:border-box;'/><br/>\
<button type='button' onclick='downloadConfig()' class='ok-btn'>Download</button>\
<div id='exportStatus' style='margin-top:0.3rem;font-size:0.8rem;color:#888;'></div></td></tr>\
<tr><td>Import</td><td><input type='password' id='impPass' placeholder='Passphrase' style='width:100%%;margin-bottom:0.3rem;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:8px;color:#fff;padding:0.5rem;font-size:0.8rem;box-sizing:border-box;'/><br/>\
<label style='display:inline-block;padding:0.5rem 1rem;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:8px;color:#888;font-size:0.8rem;cursor:pointer;'>\
<input type='file' id='cfgFile' accept='.json' style='display:none;'/>\
<span id='cfgFileName'>Choose file</span></label><br/>\
<button type='button' onclick='uploadConfig()' class='ok-btn'>Upload</button>\
<div id='importStatus' style='margin-top:0.3rem;font-size:0.8rem;color:#888;'></div></td></tr></table>\
<h3 style='font-size:0.75rem;color:#555;margin:1rem 0 0.5rem;'>Reboot</h3>\
<form action='' method='GET'>\
<table><tr><td></td><td><input type='submit' name='reset' value='Reboot' class='red-btn'/></td></tr></table>\
</form></div>\
<div id='rebootScreen' style='display:none;text-align:center;padding:2rem 0;'>\
<p style='color:#888;margin-bottom:0.5rem;' id='rebootMsg'>Rebooting...</p>\
<p style='font-size:1.5rem;font-weight:600;color:#fff;' id='countdown'></p></div>\
<script>\
document.getElementById('otaFile').addEventListener('change',function(){document.getElementById('otaFileName').textContent=this.files[0]?this.files[0].name:'Choose .bin';});\
function uploadOTA(){\
var f=document.getElementById('otaFile').files[0];\
if(!f){document.getElementById('otaStatus').textContent='Select a file';return;}\
document.getElementById('otaStatus').textContent='Uploading...';document.getElementById('otaBar').style.display='block';\
var xhr=new XMLHttpRequest();xhr.open('POST','/api/ota-upload',true);\
xhr.upload.onprogress=function(e){if(e.lengthComputable){var p=Math.round(e.loaded/e.total*100);document.getElementById('otaBarFill').style.width=p+'%%';document.getElementById('otaStatus').textContent='Uploading '+p+'%%';}};\
xhr.onload=function(){try{var d=JSON.parse(xhr.responseText);if(d.ok){document.getElementById('wrap').style.display='none';document.getElementById('rebootScreen').style.display='block';var c=10;var el=document.getElementById('countdown');var t=setInterval(function(){c--;el.textContent=c;if(c<=0){clearInterval(t);window.location.href='/';}},1000);}else{document.getElementById('otaBarFill').style.width='0';document.getElementById('otaBar').style.display='none';document.getElementById('otaStatus').textContent=d.msg||'Failed';}}catch(e){document.getElementById('otaStatus').textContent='Error';}};\
xhr.onerror=function(){document.getElementById('otaStatus').textContent='Connection error';};xhr.send(f);}\
document.getElementById('cfgFile').addEventListener('change',function(){document.getElementById('cfgFileName').textContent=this.files[0]?this.files[0].name:'Choose file';});\
function downloadConfig(){var pass=document.getElementById('expPass').value;document.getElementById('exportStatus').textContent='Downloading...';fetch('/api/config-export',{method:'POST',body:JSON.stringify({pass:pass}),headers:{'Content-Type':'application/json'}}).then(function(r){if(!r.ok)throw new Error();var cd=r.headers.get('Content-Disposition')||'';var fn='config.json';var m=cd.match(/filename=\"([^\"]+)\"/);if(m)fn=m[1];return r.blob().then(function(b){return{b:b,fn:fn};});}).then(function(o){var url=URL.createObjectURL(o.b);var a=document.createElement('a');a.href=url;a.download=o.fn;document.body.appendChild(a);a.click();setTimeout(function(){URL.revokeObjectURL(url);a.remove();},100);document.getElementById('exportStatus').textContent='Done';}).catch(function(){document.getElementById('exportStatus').textContent='Failed';});}\
function uploadConfig(){var f=document.getElementById('cfgFile').files[0];var pass=document.getElementById('impPass').value;if(!f){document.getElementById('importStatus').textContent='Select a file';return;}var r=new FileReader();r.onload=function(){document.getElementById('importStatus').textContent='Uploading...';var h={'Content-Type':'application/json'};if(pass)h['X-Config-Pass']=pass;fetch('/api/config-import',{method:'POST',body:r.result,headers:h}).then(function(r){return r.json();}).then(function(d){if(d.ok){document.getElementById('wrap').style.display='none';document.getElementById('rebootScreen').style.display='block';var c=5;var el=document.getElementById('countdown');var t=setInterval(function(){c--;el.textContent=c;if(c<=0){clearInterval(t);window.location.href='/';}},1000);}else{document.getElementById('importStatus').textContent=d.msg||'Failed';}});};r.readAsText(f);}\
</script>\
<div style='text-align:center;margin-top:1.5rem;'><a href='/' style='color:#555;text-decoration:none;font-size:0.8rem;'>← Home</a></div>\
</div></body></html>"

/* Danger Zone removed — VPN and web bind restrictions no longer shown */
