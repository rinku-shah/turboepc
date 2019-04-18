
void RijndaelKeySchedule( unsigned char const* );
void KeyAdd(unsigned char*, unsigned char*, int round);
int ByteSub(unsigned char*);
void ShiftRow(unsigned char*);
void MixColumn(unsigned char*);
void RijndaelEncrypt( unsigned char const*, unsigned char* );

