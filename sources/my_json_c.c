#include <stdio.h>
#include <json-c/json.h>
#include <sys/stat.h> // used for file size

#include "../headers/my_json_c.h"

const char *queryAttrString(struct json_object *inputObject, char *attrName, int idx) {
	struct json_object *er_class;
	er_class = json_object_array_get_idx(inputObject, idx);

	struct json_object *attr;
	json_object_object_get_ex(er_class, attrName, &attr);

	return json_object_get_string(attr);
}

int queryAttrInteger(struct json_object *inputObject, char *attrName, int idx) {
	struct json_object *er_class;
	er_class = json_object_array_get_idx(inputObject, idx);

	struct json_object *attr;
	json_object_object_get_ex(er_class, attrName, &attr);

	return json_object_get_int(attr);
}

size_t returnFileSize(char *filePath) {
	// Get the size of a json file
	struct stat st;
	stat(filePath, &st);
	size_t size = st.st_size; // size in bytes

	return size;
}
