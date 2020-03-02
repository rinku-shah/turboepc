/**
 * Tulio Alberton Ribeiro
 * 
 * LaSIGE - Large-Scale Informatics Systems Laboratory
 * 
 * 03/2016
 * 
 * Without warrant
 * 
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 */

package org.onosproject.p4tutorial.epc;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.concurrent.Callable;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import org.slf4j.Logger;
import static org.slf4j.LoggerFactory.getLogger;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class FT{
	private static final Logger log = getLogger(EpcApp.class);


	protected static Logger logger = LoggerFactory.getLogger(FT.class);
	private String controllerId;
		
	public static ConcurrentHashMap<String, String> uekey_sgw_teid_map = new ConcurrentHashMap<String, String>();
	public static ConcurrentHashMap<String, String> sgw_teid_uekey_map = new ConcurrentHashMap<String, String>();
	public static ConcurrentHashMap<String, String> uekey_ueip_map = new ConcurrentHashMap<String, String>();

	// Key: UE_Key, Value: State (TRUE: Active, FALSE: Idle)
	public static ConcurrentHashMap<String, String> ue_state = new ConcurrentHashMap<String, String>();	
	
	public static ConcurrentHashMap<String, String> SGW_PGW_TEID_MAP = new ConcurrentHashMap<String, String>();

	static Long putCount=(long) 0;
	
	static Long getCount=(long) 0;
	
	//putArr of length 20
	static long putArr[] = new long[100];


	public static void put(int msgId,String dgwDpId, String mapName, String key, String val){
		putCount++;
		putArr[msgId]++;
		if(Constants.CENTRALIZED){
			/*putCount++;*/
			String tmpStore = FT.getStoreNameFromDGW(dgwDpId);
			if(Constants.DEBUG) {
				log.warn("msgId = {}", msgId);
				log.warn("received tmpStore = {}", tmpStore);
			}
			StringBuilder k = new StringBuilder();
			k.append(tmpStore).append(Constants.STOREKEYSEPARATOR).append(key);
			if(mapName.equals("uekey_sgw_teid_map")){
				uekey_sgw_teid_map.put(k.toString(),val);
			}
			else if(mapName.equals("sgw_teid_uekey_map")){
				sgw_teid_uekey_map.put(k.toString(),val);
			}
			else if(mapName.equals("uekey_ueip_map")){
				uekey_ueip_map.put(k.toString(),val);
			}
			else if(mapName.equals("ue_state")){
				ue_state.put(k.toString(),val);
			}
			else if(mapName.equals("SGW_PGW_TEID_MAP")){
				if(Constants.MYDEBUG) {
					log.warn(" in SGW_PGW_TEID_MAP put key  = {}", k.toString());
					log.warn(" in SGW_PGW_TEID_MAP put val  = {}", val);
				}
				SGW_PGW_TEID_MAP.put(k.toString(),val);
			}
		}
		else {

		}
	}	
	
	public static String get(String dgwDpId,String mapName, String key) {
			String val=null;
			getCount++;
			String tmpStore = FT.getStoreNameFromDGW(dgwDpId);
			StringBuilder k = new StringBuilder();
			k.append(tmpStore).append(Constants.STOREKEYSEPARATOR).append(key);

			if(mapName.equals("uekey_sgw_teid_map")){
				val = uekey_sgw_teid_map.get(k.toString());
			}
			else if(mapName.equals("sgw_teid_uekey_map")){
				val = sgw_teid_uekey_map.get(k.toString());
			}
			else if(mapName.equals("uekey_ueip_map")){
				val = uekey_ueip_map.get(k.toString());
			}
			else if(mapName.equals("ue_state")){
				val = ue_state.get(k.toString());
			}
			else if(mapName.equals("SGW_PGW_TEID_MAP")){
				if(Constants.MYDEBUG) {
					log.warn(" in SGW_PGW_TEID_MAP get key  = {}", k.toString());
//					log.warn(" in SGW_PGW_TEID_MAP put val  = {}", val);
				}
				val = SGW_PGW_TEID_MAP.get(k.toString());
//				log.warn("val in get = {}",val);
			}
//			if(val != null){
				return val;
	}

	public static void del(int msgId,String dgwDpId,String mapName, String key){
		//putCount++;
		//putArr[msgId]++;
		if(Constants.CENTRALIZED){
			//String val="none";
			String tmpStore = FT.getStoreNameFromDGW(dgwDpId);
			StringBuilder k = new StringBuilder();
			k.append(tmpStore).append(Constants.STOREKEYSEPARATOR).append(key);

			if(mapName.equals("uekey_sgw_teid_map")){
				uekey_sgw_teid_map.remove(k.toString());
			}
			else if(mapName.equals("sgw_teid_uekey_map")){
				sgw_teid_uekey_map.remove(k.toString());
			}
			else if(mapName.equals("uekey_ueip_map")){
				uekey_ueip_map.remove(k.toString());
			}
			else if(mapName.equals("ue_state")){
				ue_state.remove(k.toString());
			}
			else if(mapName.equals("SGW_PGW_TEID_MAP")){
				if(Constants.MYDEBUG) {
					log.warn(" in SGW_PGW_TEID_MAP del key  = {}", k.toString());
//					log.warn(" in SGW_PGW_TEID_MAP put val  = {}", val);
				}
				SGW_PGW_TEID_MAP.remove(k.toString());
			}
		}

	}
	
	public static String getStoreNameFromDGW(String dgw){
		String swid1 = "";
		if(dgw.charAt(0)=='s'){
			// means we get "s1", "s11" like switch numbers
			//log.warn("got switch name ={}",dgw);
			swid1=dgw.split("s")[1];

		}
		else{
			// we got switch ID like "1", "2", "12"
			//log.warn("got switch id ={}",dgw);
			swid1 = dgw;
		}
		int swid = Integer.parseInt(swid1);
		String store = null;
		if (swid==(Constants.DEFAULT_SWITCH_ID_1))
			store = "storeEPC1";
		else if (swid==(Constants.DEFAULT_SWITCH_ID_2))
			store = "storeEPC2";
		if (swid==(Constants.DEFAULT_SWITCH_ID_3))
			store = "storeEPC3";
		if (swid==(Constants.DEFAULT_SWITCH_ID_4))
			store = "storeEPC4";
		if (swid==(Constants.DEFAULT_SWITCH_ID_5))
			store = "storeEPC5";
		if (swid==(Constants.DEFAULT_SWITCH_ID_6))
			store = "storeEPC6";
		return store;
	}
}

