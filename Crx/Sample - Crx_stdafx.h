//THIS FILE SHOULD BE RENAMED TO "Crx_stdafx.h" AND COPIED SOMEWHERE SUCH AS
//				#include "Crx_stdafx.h"
//		IS VALID. ALSO REMEMBER THAT THE LIBRARY DOES NOT INCLUDE "Crx_stdafx.h"
//		IF IT IS RUN AS A HEADER ONLY LIBRARY. IN THAT CASE, USE THIS FILE AS
//		A GUIDE, OR ACTUALLY CREATE "Crx_stdafx.h" AND ADD THE STATEMENT
//				#include "Crx_stdafx.h"
//		SOMEWHERE YOURSELF BEFORE INCLUDING ANY FILES FROM THIS LIBRARY
//		FOR "CRX__CONFIG__MODE", USE, 
//				0: FOR HEADER ONLY
//				1: FOR STAND ALONE
//				2: FOR INTERFACE
//				3: FOR DLL STAND ALONE
//				4: FOR DLL INTERFACE
#include "Crx/Crx.options.h"

#define CRX__CONFIG__MODE 1


//crx::Var
#define CRX__VAR__CONFIG__ARE_EXCEPTIONS_ENABLED  CRXM__TRUE
#define CRX__VAR__CONFIG__INT_MODE  CRX__VAR__OPTION__INT_MODE__32BIT
#define CRX__VAR__CONFIG__HASH_TABLE_IMPLEMENTATION  CRX__VAR__OPTION__HASH_TABLE_IMPLEMENTATION__SORTED_KHASH
#define CRX__VAR__CONFIG__ERROR_MODE  CRX__VAR__OPTION__ERROR_MODE__PROPOGATER
#define CRX__VAR__CONFIG__ARRAY_IMPLEMENTATION  CRX__VAR__OPTION__ARRAY_IMPLEMENTATION__VARRING
#define CRX__VAR__CONFIG__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE  CRXM__TRUE