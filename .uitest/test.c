/* Compile + render harness for the AeroLink web UI page templates.
 *
 * 1) Format safety: every macro that the firmware passes to snprintf() is
 *    compiled through snprintf() here with -Werror=format, so a mismatched
 *    or accidental conversion specifier fails the build.
 * 2) Rendering: writes assembled sample pages to .uitest/out/ so the UI can
 *    be inspected in a browser without flashing an ESP32.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pages.h"

static char big[1 << 20];

static void wfile(const char *path, const char *data)
{
    FILE *f = fopen(path, "wb");
    if (!f) { fprintf(stderr, "cannot write %s\n", path); exit(1); }
    fwrite(data, 1, strlen(data), f);
    fclose(f);
}

int main(int argc, char **argv)
{
    int render = (argc > 1 && strcmp(argv[1], "render") == 0);

    /* ---- format-string compile checks (-Werror=format) ---- */
    snprintf(big, sizeof(big), INDEX_CHUNK_TAIL, "1.4.2", "2026-09-30", "12:00:00");

#if !CONFIG_ETH_UPLINK
    snprintf(big, sizeof(big), SCAN_PAGE, 5, 12, "<th>Action</th>",
             "<tr><td>x</td><td>y</td></tr>");
    snprintf(big, sizeof(big), SETUP_CHUNK_FORM, "apssid", "uplinkssid");
    snprintf(big, sizeof(big), CONFIG_CHUNK_STA, "ssid", "sel", "", "",
             "user", "ident", "sel", "", "", "", "sel", "", "", "",
             "checked", "", "aa:bb:cc:dd:ee:ff");
#endif

    snprintf(big, sizeof(big), CONFIG_CHUNK_AP,
             "apssid", "192.168.4.1", "aerolink", "1.1.1.1", "aa:bb:cc:dd:ee:ff",
#if CONFIG_ETH_UPLINK
             6,
#endif
             "selected", "", "", "checked", "checked", "", "checked");

    snprintf(big, sizeof(big), CONFIG_CHUNK_STATIC, "0.0.0.0", "255.255.255.0", "0.0.0.0");
    snprintf(big, sizeof(big), CONFIG_CHUNK_RC,
             "checked", "", "#5fd3a4", "Listening", "", 23, "checked", "checked", 3600UL);
    snprintf(big, sizeof(big), CONFIG_CHUNK_PCAP,
             "selected", "", "", "#5fd3a4", "Connected", 123UL, 4UL, 1500, "192.168.4.2");

    printf("format checks passed (eth=%d)\n", CONFIG_ETH_UPLINK);
    if (!render) return 0;

    /* ---- render sample pages ---- */
#if !CONFIG_ETH_UPLINK
    {   /* /scan */
        const char *rows =
            "<tr><td>HomeWiFi</td><td style='white-space:nowrap;'><span class='signal-bars'>"
            "<span class='bar active signal-excellent' style='height:4px;'></span>"
            "<span class='bar active signal-excellent' style='height:8px;'></span>"
            "<span class='bar active signal-excellent' style='height:12px;'></span>"
            "<span class='bar active signal-excellent' style='height:16px;'></span></span>"
            "<span style='color:#888;font-size:0.8rem;margin-left:0.5em;'>-42 dBm</span></td>"
            "<td>6 <span style='color:#888;font-size:0.75rem;'>2.4G</span></td><td>WPA2</td>"
            "<td><a href='/setup?ssid=HomeWiFi' class='connect-button'>Connect</a></td></tr>"
            "<tr><td>Neighbours 5G</td><td style='white-space:nowrap;'><span class='signal-bars'>"
            "<span class='bar active signal-fair' style='height:4px;'></span>"
            "<span class='bar active signal-fair' style='height:8px;'></span>"
            "<span class='bar'></span><span class='bar'></span></span>"
            "<span style='color:#888;font-size:0.8rem;margin-left:0.5em;'>-67 dBm</span></td>"
            "<td>44 <span style='color:#888;font-size:0.75rem;'>5G</span></td><td>WPA3</td>"
            "<td><a href='/setup?ssid=x' class='connect-button'>Connect</a></td></tr>"
            "<tr><td colspan='5' style='text-align:center; color:#00d9ff;'>"
            "<span style='display:inline-block; animation: pulse 1s infinite;'>&#128225; Scanning...</span></td></tr>";
        snprintf(big, sizeof(big), SCAN_PAGE, 5, 12, "<th>Action</th>", rows);
        wfile(".uitest/out/scan.html", big);
    }
    {   /* /setup */
        char form[65536];
        snprintf(form, sizeof(form), SETUP_CHUNK_FORM, "AeroLink", "HomeWiFi");
        snprintf(big, sizeof(big), "%s%s", SETUP_CHUNK_HEAD, form);
        wfile(".uitest/out/setup.html", big);
    }
#endif

    {   /* / */
        char tmp[65536];
        snprintf(big, sizeof(big), "%s%s%s",
                 INDEX_CHUNK_HEAD,
                 "<div style='text-align: right; margin-bottom: 0.5rem;'>"
                 "<a href='/?logout=1' style='padding: 0.4rem 1rem; background: rgba(255,255,255,0.04); color: #888; border: 1px solid rgba(255,255,255,0.08); border-radius: 6px; text-decoration: none; font-size: 0.75rem; font-weight: 500; transition: all 0.3s;'>Logout</a>"
                 "</div>",
                 INDEX_CHUNK_STATUS_OPEN);
        strcat(big,
            "<tr><td>SSID:</td><td><strong>AeroLink</strong></td></tr>"
            "<tr><td>AP IP:</td><td>192.168.4.1</td></tr>"
            "<tr><td>AP Clients:</td><td>3</td></tr>"
            "<tr><td>Uplink:</td><td><strong>Connected (-58 dBm)</strong></td></tr>"
            "<tr><td>STA IP:</td><td>192.168.1.42</td></tr>"
            "<tr><td>Bytes:</td><td>1.2 MB sent / 8.4 MB received</td></tr>"
            "<tr><td>Monitoring:</td><td><span style='color: #888;'>Off</span></td></tr>"
            "<tr><td>Uptime:</td><td>02h 14m (since 09:30)</td></tr>");
        strcat(big, INDEX_CHUNK_STATUS_CLOSE);
        strcat(big, INDEX_CHUNK_BUTTONS);
        strcat(big,
            "<div style='margin-top: 1rem; padding: 0.8rem; background: rgba(76,175,80,0.1); color: #4caf50; border: 1px solid rgba(76,175,80,0.2); border-radius: 12px; font-size: 0.8rem;'>Logged in</div>"
            "<div class='glass' style='margin-top: 1rem;'>"
            "<h2>&#128274; Login</h2>"
            "<form action='/' method='POST'>"
            "<input type='text' name='username' value='admin' autocomplete='username' style='display:none' aria-hidden='true' tabindex='-1'/>"
            "<input type='password' name='login_password' placeholder='Enter password' autocomplete='current-password' style='width: 100%; padding: 0.6rem; margin-bottom: 0.6rem; background: rgba(255,255,255,0.04); border: 1px solid rgba(255,255,255,0.08); border-radius: 8px; color: #fff; font-size: 0.85rem; box-sizing: border-box;'/>"
            "<input type='submit' value='Login' style='width: 100%; padding: 0.6rem; background: rgba(255,255,255,0.08); color: #fff; border: 1px solid rgba(255,255,255,0.1); border-radius: 8px; font-size: 0.85rem; font-weight: 500; cursor: pointer; box-sizing: border-box;'/>"
            "</form></div>"
            "<div class='glass' style='margin-top: 1rem;'>"
            "<h2>&#128273; Change Password</h2>"
            "<form action='/' method='POST'>"
            "<input type='password' name='new_password' placeholder='New password (empty to disable)' autocomplete='new-password' style='width: 100%; padding: 0.6rem; margin-bottom: 0.6rem; background: rgba(255,255,255,0.04); border: 1px solid rgba(255,255,255,0.08); border-radius: 8px; color: #fff; font-size: 0.85rem; box-sizing: border-box;'/>"
            "<input type='password' name='confirm_password' placeholder='Confirm password' autocomplete='new-password' style='width: 100%; padding: 0.6rem; margin-bottom: 0.6rem; background: rgba(255,255,255,0.04); border: 1px solid rgba(255,255,255,0.08); border-radius: 8px; color: #fff; font-size: 0.85rem; box-sizing: border-box;'/>"
            "<input type='submit' value='Change Password' style='width: 100%; padding: 0.6rem; background: rgba(255,255,255,0.08); color: #fff; border: 1px solid rgba(255,255,255,0.1); border-radius: 8px; font-size: 0.85rem; font-weight: 500; cursor: pointer; box-sizing: border-box;'/>"
            "<p style='margin-top: 0.5rem; color: #555; font-size: 0.7rem;'>Leave empty to disable password protection.</p>"
            "</form></div>");
        snprintf(tmp, sizeof(tmp), INDEX_CHUNK_TAIL, "1.4.2", "2026-09-30", "12:00:00");
        strcat(big, tmp);
        wfile(".uitest/out/index.html", big);
    }

    {   /* /config */
        char sec[65536];
        snprintf(big, sizeof(big), "%s%s%s", CONFIG_CHUNK_HEAD,
                 "<a href='/?logout=1' style='padding: 0.4rem 1rem; background: rgba(255,82,82,0.15); color: #ff5252; border: 1px solid #ff5252; border-radius: 6px; text-decoration: none; font-size: 0.85rem; font-weight: 500;'>Logout</a>",
                 CONFIG_CHUNK_SCRIPT);
        snprintf(sec, sizeof(sec), CONFIG_CHUNK_AP,
                 "AeroLink", "192.168.4.1", "aerolink", "1.1.1.1", "aa:bb:cc:dd:ee:ff",
#if CONFIG_ETH_UPLINK
                 6,
#endif
                 "selected", "", "", "checked", "checked", "", "checked");
        strcat(big, sec);
#if !CONFIG_ETH_UPLINK
        snprintf(sec, sizeof(sec), CONFIG_CHUNK_STA, "HomeWiFi", "selected", "", "",
                 "", "", "selected", "", "", "", "selected", "", "", "",
                 "", "", "aa:bb:cc:dd:ee:ff");
        strcat(big, sec);
#endif
        snprintf(sec, sizeof(sec), CONFIG_CHUNK_STATIC, "0.0.0.0", "255.255.255.0", "0.0.0.0");
        strcat(big, sec);
        snprintf(sec, sizeof(sec), CONFIG_CHUNK_RC,
                 "checked", "", "#5fd3a4", "Listening", "", 23, "checked", "checked", 3600UL);
        strcat(big, sec);
        snprintf(sec, sizeof(sec), CONFIG_CHUNK_PCAP,
                 "selected", "", "", "#5fd3a4", "Not connected", 123UL, 4UL, 1500, "192.168.4.2");
        strcat(big, sec);
        strcat(big, CONFIG_CHUNK_TAIL);
        strcat(big,
            "<table>"
            "<tr><td>Running</td><td>ota_0</td></tr>"
            "<tr><td>Chip</td><td>ESP32</td></tr>"
            "<tr><td>Version</td><td>1.4.2</td></tr>"
            "<tr><td>Built</td><td>2026-09-30 12:00:00</td></tr>"
            "</table>");
        strcat(big, CONFIG_CHUNK_TAIL2);
        wfile(".uitest/out/config.html", big);
    }

    {   /* /mappings */
        char tmp[65536];
        snprintf(big, sizeof(big), "%s%s%s%s", MAPPINGS_CHUNK_HEAD,
                 "<div class='modal-overlay show' id='errorModal'><div class='modal-box'>"
                 "<h3>Error</h3><p>Invalid MAC address</p>"
                 "<button onclick=\"document.getElementById('errorModal').classList.remove('show');\">OK</button></div></div>",
                 MAPPINGS_CHUNK_MID1,
                 "<a href='/?logout=1' style='padding: 0.4rem 1rem; background: rgba(255,82,82,0.15); color: #ff5252; border: 1px solid #ff5252; border-radius: 6px; text-decoration: none; font-size: 0.85rem; font-weight: 500;'>Logout</a>");
        strcat(big, MAPPINGS_CHUNK_MID2);
        strcat(big,
            "<tr><td>AA:BB:CC:DD:EE:01</td><td>192.168.4.100</td><td>Phone</td><td>1.2 MB / 8.4 MB</td>"
            "<td><button type='button' class='select-button' onclick=\"fillDhcpForm('AA:BB:CC:DD:EE:01','192.168.4.100','Phone')\">Select</button></td></tr>"
            "<tr><td>AA:BB:CC:DD:EE:02</td><td>192.168.4.101</td><td>-</td><td>-</td>"
            "<td><button type='button' class='select-button' onclick=\"fillDhcpForm('AA:BB:CC:DD:EE:02','192.168.4.101','')\">Select</button></td></tr>");
        strcat(big, MAPPINGS_CHUNK_MID3);
        strcat(big, "<small style='color:#888;'>Pool: 192.168.4.100 - 192.168.4.199</small>");
        strcat(big, MAPPINGS_CHUNK_MID3B);
        strcat(big,
            "<tr><td>AA:BB:CC:DD:EE:01</td><td>192.168.4.100</td><td>Phone</td>"
            "<td><a href='/mappings?del_dhcp_mac=AA:BB:CC:DD:EE:01' class='red-button'>Delete</a></td></tr>"
            "<tr><td>AA:BB:CC:DD:EE:03</td><td><span style='color:#ff5252;font-weight:bold;'>BLOCKED</span></td><td>-</td>"
            "<td><a href='/mappings?del_dhcp_mac=AA:BB:CC:DD:EE:03' class='red-button'>Delete</a></td></tr>");
        strcat(big, MAPPINGS_CHUNK_MID4);
        strcat(big, MAPPINGS_CHUNK_PORTFWD_HEAD);
        strcat(big,
            "<tr><td>STA</td><td>TCP</td><td>8080</td><td>nas</td><td>80</td>"
            "<td><a href='/mappings?del_proto=TCP&del_port=8080' class='red-button'>Delete</a></td></tr>");
        strcat(big, MAPPINGS_CHUNK_PORTFWD_TAIL);
        strcat(big, MAPPINGS_CHUNK_PAGE_FOOTER);
        (void)tmp;
        wfile(".uitest/out/mappings.html", big);
    }

    {   /* /firewall */
        snprintf(big, sizeof(big), "%s%s%s", FIREWALL_CHUNK_HEAD, FIREWALL_CHUNK_MID1,
                 "<a href='/?logout=1' style='padding: 0.4rem 1rem; background: rgba(255,82,82,0.15); color: #ff5252; border: 1px solid #ff5252; border-radius: 6px; text-decoration: none; font-size: 0.85rem; font-weight: 500;'>Logout</a>");
        strcat(big, FIREWALL_CHUNK_MID2);
        strcat(big,
            "<div class='acl-section'>"
            "<h3>To ESP (input)</h3>"
            "<div class='stats'><span class='allowed'>Allowed: 1520</span>"
            "<span class='denied'>Denied: 12</span>"
            "<span>No match: 430</span>"
            "<a href='/firewall?clear_acl=0' class='orange-button' style='float:right;'>Clear</a></div>"
            "<table class='data-table'><thead><tr>"
            "<th>#</th><th>Proto</th><th>Source</th><th>SPort</th>"
            "<th>Dest</th><th>DPort</th><th>Action</th><th>Hits</th><th></th>"
            "</tr></thead><tbody>"
            "<tr><td>0</td><td>TCP</td><td>Phone</td><td>*</td><td>192.168.4.1</td><td>23</td>"
            "<td>Allow</td><td>42</td>"
            "<td><a href='/firewall?del_acl=0&del_idx=0' class='red-button'>Del</a></td></tr>"
            "<tr><td colspan='9' style='text-align:center; color:#888;'>No rules (all packets allowed)</td></tr>"
            "</tbody></table></div>"
            "<div class='acl-section'>"
            "<h3>From ESP (forward)</h3>"
            "<div class='stats'><span class='allowed'>Allowed: 0</span>"
            "<span class='denied'>Denied: 0</span><span>No match: 0</span>"
            "<a href='/firewall?clear_acl=1' class='orange-button' style='float:right;'>Clear</a></div>"
            "<table class='data-table'><thead><tr>"
            "<th>#</th><th>Proto</th><th>Source</th><th>SPort</th>"
            "<th>Dest</th><th>DPort</th><th>Action</th><th>Hits</th><th></th>"
            "</tr></thead><tbody>"
            "<tr><td colspan='9' style='text-align:center; color:#888;'>No rules (all packets allowed)</td></tr>"
            "</tbody></table></div>");
        strcat(big, FIREWALL_CHUNK_TAIL);
        wfile(".uitest/out/firewall.html", big);
    }

    printf("rendered sample pages to .uitest/out/\n");
    return 0;
}
