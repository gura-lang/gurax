//==============================================================================
// SampleRecord.h
//==============================================================================
struct SampleRecord {
	const char* name;
	const char* email;
	const char* gender;
	int age;
	const char* birthDay;
	const char* phone;
	static const SampleRecord tbl[];
};
