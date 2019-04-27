import json

with open('sgw1.p4cfg') as f:
  data = json.load(f)

# Output: {'name': 'Bob', 'languages': ['English', 'Fench']}
print(data)
# print(data['tables']['service_req_uekey_sgwteid_map'])
table_data = data['tables']['service_req_uekey_sgwteid_map'];
print table_data['rules'][0]['action']['data']
print table_data['rules'][0]['match']['ue_service_req.ue_key']
ue_key = table_data['rules'][0]['match']['ue_service_req.ue_key']['value']
old_sgwteid = table_data['rules'][0]['action']['data']['sgwteid']['value']
# print "old_sgw_teid = ", old_sgwteid
rule_name = table_data['rules'][0]['name']
action_type =  table_data['rules'][0]['action']['type']
# print "rule name = ", rule_name
# print "action type = ", action_type
old_rules = table_data['rules'][0];
l=[]
print old_rules;
new_rule = int(rule_name)+1
y={}


for i in range(1,101):
    # print i
    new_rule_name = int(rule_name)+i
    new_ue_key = int(ue_key)+i
    new_sgw_teid = int(old_sgwteid) + i
    # print new_rule_name
    tmp_ue_key={}
    tmp_ue_key['value']=str(new_ue_key)
    # print tmp_ue_key
    ue_ser_req={}
    ue_ser_req['ue_service_req.ue_key'] = tmp_ue_key
    rules={}
    rules['name']=str(new_rule_name)
    
    # rules['match']= table_data['rules'][0]['match']
    rules['match']= ue_ser_req
    action = {}
    action['type'] = action_type
    tmp_sgwteid = {}
    tmp_sgwteid['value'] = str(new_sgw_teid)
    x={}
    x['sgwteid']=tmp_sgwteid
    action['data'] = x
    # print action
    rules['action'] = action
    # with open('data.json', 'w') as outfile:
    #     json.dump(rules, outfile)
    l.append(rules)
    # old_rules.append(rules)
    print rules

# print old_rules
print l
y['rules']=l
print y
tmp_rules={}
tmp_rules["rules"] = l
table_name1 = {}
table_name1["ingress::service_req_uekey_sgwteid_map"] = tmp_rules;
start={}
start["tables"]= table_name1
print "\n"
print start
with open('data1.p4cfg', 'w') as outfile:
    json.dump(l, outfile)

# print "\n"
# print data['tables']

# print "\n"
# print data
    
