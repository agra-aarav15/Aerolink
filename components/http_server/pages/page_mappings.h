/* Mappings page templates */
#include "router_config.h"

/* Mappings Page - Chunked for streaming */
#define MAPPINGS_CHUNK_HEAD "<html>\
<head>\
<meta name='viewport' content='width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0'>\
<meta charset='UTF-8'>\
<title>AeroLink — Mappings</title>\
<link rel='icon' href='favicon.png'>\
<link href='https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600;700&display=swap' rel='stylesheet'>\
</head>\
<style>\
*{box-sizing:border-box;margin:0;padding:0;}\
body{font-family:'Inter',sans-serif;background:#000;color:#fff;padding:1.5rem;min-height:100vh;display:flex;justify-content:center;}\
#wrap{width:100%;max-width:800px;}\
h1{font-size:1.1rem;font-weight:300;color:#fff;letter-spacing:3px;text-transform:uppercase;margin-bottom:0.3rem;}\
h2{font-size:0.7rem;font-weight:600;color:#555;text-transform:uppercase;letter-spacing:2px;margin:1.2rem 0 0.6rem;border-bottom:1px solid rgba(255,255,255,0.05);padding-bottom:0.4rem;}\
.glass{background:rgba(255,255,255,0.04);backdrop-filter:blur(20px);-webkit-backdrop-filter:blur(20px);border:1px solid rgba(255,255,255,0.08);border-radius:16px;padding:1.2rem;margin-bottom:1rem;}\
a.home{display:inline-flex;align-items:center;gap:0.5rem;color:#555;text-decoration:none;font-size:0.75rem;margin-bottom:1.2rem;transition:color 0.3s;}\
a.home:hover{color:#aaa;}\
@keyframes fadeIn{from{opacity:0;transform:translateY(12px);}to{opacity:1;transform:translateY(0);}}\
.glass{animation:fadeIn 0.5s ease-out both;}\
.glass:nth-child(2){animation-delay:0.08s;}\
.glass:nth-child(3){animation-delay:0.16s;}\
.glass:nth-child(4){animation-delay:0.24s;}\
.tbl tbody tr{animation:fadeIn 0.3s ease-out both;}\
.ok-btn{transition:all 0.3s ease,box-shadow 0.3s;}\
.ok-btn:hover{box-shadow:0 0 10px rgba(100,149,237,0.2);}\
.tbl{width:100%%;border-collapse:collapse;}\
.tbl th{font-size:0.6rem;font-weight:600;color:#444;text-transform:uppercase;letter-spacing:1px;text-align:left;padding:0.5rem;border-bottom:1px solid rgba(255,255,255,0.06);}\
.tbl td{padding:0.5rem;border-bottom:1px solid rgba(255,255,255,0.03);font-size:0.8rem;color:#ccc;}\
.tbl tbody tr:hover td{background:rgba(255,255,255,0.02);}\
table{width:100%%;border-collapse:collapse;}\
td{padding:0.3rem 0;vertical-align:top;}\
td:first-child{color:#555;font-size:0.75rem;padding-right:0.75rem;width:30%%;text-align:right;text-transform:uppercase;letter-spacing:0.5px;}\
input[type='text'],input[type='number'],select{width:100%%;max-width:100%;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:8px;color:#fff;padding:0.5rem;font-size:0.8rem;box-sizing:border-box;overflow:hidden;}\
input:focus,select:focus{outline:none;border-color:rgba(255,255,255,0.2);}\
input::placeholder{color:#333;}\
select{cursor:pointer;background-image:url(\"data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='10' height='6'%3E%3Cpath d='M1 1l4 4 4-4' stroke='%23555' stroke-width='1.5' fill='none'/%3E%3C/svg%3E\");background-repeat:no-repeat;background-position:right 0.5rem center;padding-right:1.5rem;-webkit-appearance:none;}\
select option{background:#111;color:#fff;}\
.ok-btn{background:rgba(255,255,255,0.08);color:#fff;border:1px solid rgba(255,255,255,0.1);border-radius:8px;padding:0.5rem;font-size:0.8rem;cursor:pointer;width:100%%;margin-top:0.2rem;}\
.ok-btn:hover{background:rgba(255,255,255,0.14);}\
.rbtn{background:rgba(244,67,54,0.1);color:#f44336;border:1px solid rgba(244,67,54,0.15);border-radius:6px;padding:0.3rem 0.6rem;font-size:0.7rem;cursor:pointer;}\
.gbtn{background:rgba(76,175,80,0.1);color:#4caf50;border:1px solid rgba(76,175,80,0.15);border-radius:6px;padding:0.3rem 0.6rem;font-size:0.7rem;cursor:pointer;}\
.sbtn{background:rgba(255,255,255,0.06);color:#aaa;border:1px solid rgba(255,255,255,0.08);border-radius:6px;padding:0.3rem 0.6rem;font-size:0.7rem;cursor:pointer;}\
.sbtn:hover{background:rgba(255,255,255,0.1);}\
.modal{display:none;position:fixed;top:0;left:0;width:100%%;height:100%%;background:rgba(0,0,0,0.8);z-index:1000;justify-content:center;align-items:center;backdrop-filter:blur(5px);}\
.modal.show{display:flex;}\
.mbox{background:#111;border:1px solid rgba(244,67,54,0.3);border-radius:12px;padding:1.5rem;max-width:350px;text-align:center;}\
.mbox h3{color:#f44336;margin-bottom:0.8rem;}\
.mbox p{color:#888;margin-bottom:1rem;font-size:0.85rem;}\
.mbox button{background:rgba(255,255,255,0.08);color:#fff;border:1px solid rgba(255,255,255,0.1);border-radius:8px;padding:0.5rem 1.5rem;cursor:pointer;}\
@media(max-width:768px){body{padding:1rem;}.tbl{display:block;overflow-x:auto;}.tbl th,.tbl td{padding:0.3rem 0.2rem;font-size:0.7rem;}}\
</style>\
<script>\
function fillDhcpForm(mac,ip,name){document.getElementById('dhcp_mac').value=mac;document.getElementById('dhcp_ip').value=ip;document.getElementById('dhcp_name').value=name;document.getElementById('dhcp_mac').scrollIntoView({behavior:'smooth',block:'center'});}\
</script>\
<body>"

#define MAPPINGS_CHUNK_MID1 "\
<div id='wrap'>\
<a href='/' class='home'>← Home</a>\
<h1>AeroLink — Mappings</h1>"

#define MAPPINGS_CHUNK_MID2 "\
<div class='glass'>\
<h2>Connected Clients</h2>\
<table class='tbl'>\
<thead><tr><th>MAC</th><th>IP</th><th>Name</th><th>Traffic</th><th>Action</th></tr></thead>\
<tbody>"

#define MAPPINGS_CHUNK_MID2_NOSTATS "\
<div class='glass'>\
<h2>Connected Clients</h2>\
<table class='tbl'>\
<thead><tr><th>MAC</th><th>IP</th><th>Name</th><th>Action</th></tr></thead>\
<tbody>"

#define MAPPINGS_CHUNK_MID3 "\
</tbody></table></div>\
<div class='glass'>\
<h2>DHCP Reservations</h2>"

#define MAPPINGS_CHUNK_MID3B "\
<table class='tbl'>\
<thead><tr><th>MAC</th><th>IP</th><th>Name</th><th>Action</th></tr></thead>\
<tbody>"

#define MAPPINGS_CHUNK_MID4 "\
</tbody></table>\
<h2>Add Reservation</h2>\
<form action='/mappings' method='GET'>\
<table>\
<tr><td>MAC</td><td><input type='text' name='dhcp_mac' id='dhcp_mac' placeholder='AA:BB:CC:DD:EE:FF'/></td></tr>\
<tr><td>IP</td><td><input type='text' name='dhcp_ip' id='dhcp_ip' placeholder='192.168.4.100'/></td></tr>\
<tr><td>Name</td><td><input type='text' name='dhcp_name' id='dhcp_name'/></td></tr>\
<tr><td></td><td><input type='submit' name='dhcp_action' value='Add' class='ok-btn'/>\
<input type='submit' name='dhcp_action' value='Block' class='rbtn' style='width:100%%;padding:0.5rem;margin-top:0.2rem;' onclick=\"document.getElementById('dhcp_ip').value='0.0.0.0';\"/></td></tr>\
</table></form></div>"

#define MAPPINGS_CHUNK_PORTFWD_HEAD "\
<div class='glass'>\
<h2>Port Forwarding</h2>\
<table class='tbl' style='table-layout:fixed;'>\
<thead><tr><th>IF</th><th>Proto</th><th>Ext</th><th>IP</th><th>Int</th><th>Action</th></tr></thead>\
<tbody>"

#if CONFIG_ETH_UPLINK
#define PORTMAP_IFACE_OPTIONS "<option value='STA'>ETH</option><option value='VPN'>VPN</option>"
#else
#define PORTMAP_IFACE_OPTIONS "<option value='STA'>STA</option><option value='VPN'>VPN</option>"
#endif

#define MAPPINGS_CHUNK_PORTFWD_TAIL "\
</tbody></table>\
<h2>Add Forward</h2>\
<form action='/mappings' method='GET'>\
<table>\
<tr><td>IF</td><td><select name='iface'>" PORTMAP_IFACE_OPTIONS "</select></td></tr>\
<tr><td>Proto</td><td><select name='proto'><option>TCP</option><option>UDP</option></select></td></tr>\
<tr><td>Ext</td><td><input type='number' name='ext_port' min='1' max='65535' placeholder='8080'/></td></tr>\
<tr><td>IP</td><td><input type='text' name='int_ip'/></td></tr>\
<tr><td>Int</td><td><input type='number' name='int_port' min='1' max='65535' placeholder='80'/></td></tr>\
<tr><td></td><td><input type='submit' name='port_action' value='Add' class='ok-btn'/></td></tr>\
</table></form></div>"

#define MAPPINGS_CHUNK_PAGE_FOOTER "\
<div style='text-align:center;margin-top:1.5rem;'><a href='/' style='color:#555;text-decoration:none;font-size:0.8rem;'>← Home</a></div>\
</div></body></html>"
