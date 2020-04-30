#ifndef SCRIPTHANDLE_H
#define SCRIPTHANDLE_H

#ifndef ANGELSCRIPT_H 
// Avoid having to inform include path if header is already include before
#include "../angelscript.h"
#endif


BEGIN_AS_NAMESPACE

class CScriptHandle 
{
public:
	// Constructors
	CScriptHandle();
	CScriptHandle(const CScriptHandle &other);
	CScriptHandle(void *ref, asITypeInfo *type);
	~CScriptHandle();

	// Copy the stored value from another any object
	CScriptHandle &operator=(const CScriptHandle &other);

	// Set the reference
	void Set(void *ref, asITypeInfo *type);

	// Compare equalness
	bool operator==(const CScriptHandle &o) const;
	bool operator!=(const CScriptHandle &o) const;
	bool Equals(void *ref, int typeId) const;

	// Dynamic cast to desired handle type
	void Cast(void **outRef, int typeId);

	// Returns the type of the reference held
	asITypeInfo *GetType();
	
	ScriptString* script_TypeName();
	ScriptString* script_TypeNamespace();

	void AddRef();
	void Release();
protected:
	// These functions need to have access to protected
	// members in order to call them from the script engine
	friend void Construct(CScriptHandle *self, void *ref, int typeId);
	friend void RegisterScriptHandle_Native( );
	friend CScriptHandle* CreateScriptHandle( ScriptString* typeName );
	
	
	friend CScriptHandle* FormatCScriptHandle(void *ref, int typeId);

	void ReleaseHandle();
	void AddRefHandle();

	// These shouldn't be called directly by the 
	// application as they requires an active context
	CScriptHandle(void *ref, int typeId);
	CScriptHandle &Assign(void *ref, int typeId);
	CScriptHandle &HandleAssign(void *ref, int typeId);

	void          *m_ref;
	asITypeInfo *m_type;
	
	int 		   RefCount;
};

void RegisterScriptHandle( );

END_AS_NAMESPACE

#endif
