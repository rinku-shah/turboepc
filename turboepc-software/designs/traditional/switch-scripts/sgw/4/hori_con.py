import json
import multiprocessing
import os
import random
import re
import socket
import threading
import time
import urllib2
from contextlib import closing
def doOnosNetcfg( controllerIP):
        """
        Notifies ONOS about the new device via Netcfg.
        """
        # srcIP = self.getSourceIp(controllerIP)
        # if not srcIP:
        #     warn("*** WARN: unable to get switch IP address, won't do netcfg\n")
        #     return

        # cfgData = {
        #     "devices": {
        #         self.onosDeviceId: self.getDeviceConfig(srcIP)
        #     }
        # }
        # with open(self.netcfgfile, 'w') as fp:
        #     json.dump(cfgData, fp, indent=4)

        # if not self.netcfg:
        #     # Do not push config to ONOS.
        #     return
        # cfgData = "bmv2-s1-netcfg.json"
        with open('bmv2-s9-netcfg.json') as data_file:
            data = json.load(data_file)
        # Build netcfg URL
        url = 'http://%s:8181/onos/v1/network/configuration/' % controllerIP
        # Instantiate password manager for HTTP auth
        pm = urllib2.HTTPPasswordMgrWithDefaultRealm()
        pm.add_password(None, url,
                        os.environ['ONOS_WEB_USER'],
                        os.environ['ONOS_WEB_PASS'])
        urllib2.install_opener(urllib2.build_opener(
            urllib2.HTTPBasicAuthHandler(pm)))
        # Push config data to controller
        req = urllib2.Request(url, json.dumps(data),
                              {'Content-Type': 'application/json'})
        try:
            f = urllib2.urlopen(req)
            print f.read()
            f.close()
        except urllib2.URLError as e:
            warn("*** WARN: unable to push config to ONOS (%s)\n" % e.reason)
# doOnosNetcfg(self,"10.0.3.214")
doOnosNetcfg("192.168.100.104")


