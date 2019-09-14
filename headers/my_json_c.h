/*
 * my_json_c.h
 * */

#ifndef MY_JSON_C
#define MY_JSON_C

const char *queryAttrString(struct json_object *inputObject, char *attrName, int idx);
int queryAttrInteger(struct json_object *inputObject, char *attrName, int idx);

#endif
