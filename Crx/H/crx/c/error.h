#if(!defined(CRX__C__ERROR___h__))
#define CRX__C__ERROR___h__

#include <boost/version.hpp>
#include "Crx/H/crx/crx.h"
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma push_macro("CRX__LIB__MODE")
	#undef CRX__LIB__MODE
	#if(!defined(CRX__CONFIG__MODE))
		#define CRX__CONFIG__MODE CRX__LIB__MODE__STAND_ALONE
	#endif
	#define CRX__LIB__MODE CRX__CONFIG__MODE
#else
	#undef CRX__LIB__MODE
	#if(!defined(CRX__LIB__C_MODE))
		#define CRX__LIB__C_MODE CRX__LIB__MODE__STAND_ALONE
	#endif
	#define CRX__LIB__MODE CRX__LIB__C_MODE
#endif
//<<START>>	INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/Array.h"
#include "Crx/H/crx/c/String.h"
//<<END>>

/* DESIGN
	- CONSIDERATIONS:
		- STRICTLY, WHAT ERROR HANDLING MACHANISM IS TO BE USED IS DETERMINED BY THE PROBLEM, AS
				THE ERROR HANDLING MECHANISMS ARE DERIVED IN THE STANDARD. HOWEVER, IN C, LEVELS 1
				AND 2 AND 3 AND 5 CAN BE IMPLEMENTED, BUT NOT LEVEL 4 OR THE UNMARKED LEVEL BETWEEN
				3 AND 4. HOWEVER, WITHOUT THE AVAILABILITY OF EITHER TYPES OF OOP AS THEY ARE DFINED
				IN THE STANDARD AND THE ABILITY TO REFLECT ON THEM AT RUNTIME, OTHER CONSIDERATIONS
				ARE BEING ADDRESSED HERE, BUT THIS DOES NOT MAKE THE APPROACH CORRECT.
		- CONSIDERATIONS OF THE DESIGN:
			- MULTIPLEXING:
				- WITHOUT A TYPE SYSTEM THAT CAN BE REFLECTED UPON, AND CAN ALLOW AN INTERFACE FOR
						ALL ERRORS TYPES, WE ARE RELYING ON NUMBERS, ON ERROR CODES, AND WE HAVE
						THE PROBLEM OF COMBINING ERROR CODES FROM DIFFERENT LIBRARIES. CONSIDER
						A LIBRARY 'X' MAKING CALLS INTO LIBRARY 'Y', AND IF 'Y' PRODUCES AN ERROR
						CODE, LIBRARY 'X' WOULD LIKE TO SIMPLY PASS THE ERROR BACK TO THE USER. THE
						PROBLEM IS THAT AN ERROR CODE OF LIBRARY 'Y' MIGHT BE THE SAME AS OF THOSE
						OF LIBRARY 'X', BUT MEAN SOME THING ELSE. IF THE LANGUAGE SUPPORTED
						EXCEPTIONS, FOR EXAMPLE, OR CLASSES AS THOSE FOUND IN C++, C# OR OTHERS,
						LIBRARY 'X' CAN SIMPLY LET THE ERROR PROPOGATE UP, OR PASS IT UP EXPLICITLY,
						WITHOUT CONCERNS.
			- TRACING:
				- SOMETIMES IT IS REQUIRED TO TRACE THE ERROR DOWN THE CALL STRACK TO WHERE IT
						STARTED FROM. WHILE EXCEPTIONS PROVIDE THAT CAPACITY, THEY ARE NOT 
						NECESSARILY CORRECT GIVEN THE PROBLEM, WHICH MIGHT NOT NECESSARILY REQUIRE
						A LEVEL 4 ERROR HANDLING, NOR ARE EXCEPTIONS AVAILABLE IN C. A COMMON
						EXAMPLE COMES FROM PARSERS.
			- ERRNO:
				- THE REPRESENTATIVE PROBLEM OF THE errno MECHANISM APPEARS TO BE
					- ERROR REPORTING: THIE IS PER THE STANDARD, WHERE IT IS DEFINED AS REPORTING 
							ERRORS TO THE OPERATOR, AND POSSIBLY ALSO THE MACHINE. CONTRAST WITH
							ERROR HANDLING, WHICH IS DEFINED AS REPORTING TO THE MACHINE ONLY.							
					- REQUIRING AS LITTLE MEMORY AS POSSIBLE. THIS INCLUDES
						- STACK MEMORY
						- HEAP MEMORY
						- MEMORY REQUIRED TO HOLD THE TEXTUAL MESSAGES.
	- ABOUT ::crx::c::error::Error
		- THIS TYPE SOLVES FOR THE FOLLOWING
			- ERROR ID: THIS IS DONE BY EMPLOYING AN ERROR CODE VALUE. THE VALUE MUST BE int32_t,
					THE TYPE OF CRX ENUM. THIS IS BECAUSE LBIRARIES MIGHT USE ENUMERATIONS FOR
					THEIR ERROR CODES. int32_t SHOULD BE THE ERROR CODES OF ANY LIBRARY I EVER
					CAME ACROSS, WHICH INCLUES THE POSIX STANDARD, AND THE WIN32 API.
			- MULTIPLEXING: THIS IS DONE BY EMPLOYING AN ERROR SPACE VALUE. CURRENTLY, THE TYPE OF
					THIS IS uint16_t. LIBRARIES DO NOT ASSIGN THEIR SPACE VALUE TO THEMSELVES, AND
					INSTEAD CrxRt IS EMPLOYED TO ASSIGN THESE VALUES. CODE REFERS TO THE SPACE ID,
					BY THE LIBRARY NAME. LIBRARY NAME CONCEPT COMES FROM THE STANDARD, AND IS THE
					ONLY THING THAT EXISTS IN THE STANDARD AND IS ALSO GUARANTEED TO BE UNIQUE THAT
					CAN BE USED TO IDENTIFY A LIBRARY. REGISTRATION OF ERROR SPACES, MEANING
					ASSOCIATION OF LIBRARY NAMES TO ERROR SPACES IS DONE BY CrxRt IMPLICITLY WHEN
					REQUIRED, BY THE FUNCTION PROVIDED BY CrxRt TO GET THE ERROR SPACE NUMBER FROM
					THE LIBRARY NAME.
			- TRACING: THIS IS A USING A DATA CONTAINER FOR THE VARIOUS ERROR ENTRIES ENCOUNTERED
					STARTING FROM THE FIRST FUNCTIONS THAT ENCOUNTERS THE ERROR, AND ENDED WITH
					THE TOP LEVEL FUNCTION WHERE THE ERROR WAS REQUESTED.
			- LOW MEMORY USAGE PER THE errno PARADIGM AS DEDUCED IN THE STANDARD. THIS IS DONE BY,
				- DIRECTING THE ERROR OBJECT TO HOLD ONE ERROR ONLY, AND NOT AN ENTIRE TRACE.
				- DIRECTING THE ERROR OBJECT TO HOLD A POINTER TO A PERSISTANT CONSTANT C STRING,
						RATHER THAN A COPY OF A STRING THAT IT MANAGED ITSELF.
			- AVOIDING THE HEAP FOR CrxRt's INNER WORKING. WHEN THE ERROR OBJECT IS DIRECTED NOT TO
					HOLD A TRACE, THE ERROR OBJECT IS GUARANTEED NOT TO USE THE HEAP IMPLICITLY.
			- ALLOWING THE ERROR TO BE OPTIONAL OR MANDATORY. THE ERROR OBJECT IS TO HAVE A POINTER
					OF IT PASSED TO THE FUNCTION WHEN THE CALLER WANTS TO KNOW ABOUT THE ERROR, OR
					THE FUNCTION DEMANDS THAT THE USER KNOW ABOUT THE ERROR. HENCE, IF THE FUNCTION
					DOES NOT DEMAND THE ERROR BE KNOWN, THE CALLER CAN CHOOSE TO PASS NULL.
			- ALLOWING THE RECIEVER OF THE ERROR HIMSELF DECIDE HOW MUCH MEMORY THE ERROR SHALL 
					CONSUME.
		- REMEMBER:
			- PER THE CORRECT FORM OF C, ONLY PRIMITIVE TYPES CAN BE RETURNED, NEVER A STRUCT OR
					SIMILAR.
			- THE ERROR TYPE MAY NOT ITSELF FAIL.
			- RETURNING A POINTER FOR THE ERROR OBJECT WOULD MEAN THAT THE USER CAN NEVER IGNORE
					IT BECAUSE HE HAS TO DE ALLOCATE. THIS WOULD ALSO EMPLOY AN OWNER SHIP 
					EXCEPTION LAW AS DEFINED IN THE STANDARD WHICH ITSELF DISCOURAGES ESPECIALLY
					IF INDICATORS ARE NEEDED.
			- RETURNING A POINTER FOR THE ERROR OBJECT WOULD ALSO MENA THAT THE ERROR OBJECT
					IS ALWAYS CREATED.
	- PROBLEMS:
		- THE ::crx::c::error::Error APPROACH REMAINS A MORE MEMORY CONSUMING APPROACH THAN 
				NECESSARY SOMETIMES. WHILE THE errorno APPROACH IS NEVER CORRECT AS PROVEN IN THE
				STANDARD, IT CAN EASILY BE CORRECTED BY RETURNING THE ERROR CODES AS FUNCTION 
				RETURNS. THIS GENERALLY DOES NOT SACRIFICE ANYTHING BECAUSE THE RETURN WOULD BE ON 
				A REGISTER, AND CODE CAN CONTINUE TO EMPLOY OTHER FACILITES OF THE GLOBAL VARIABLE
				APPROACH, SUCH AS A FUNCTION TO GET AN ERROR MESSAGE GIVEN AN ERROR CODE.
				
				IF ::crx::c::error::Error GETS USED INSTEAD OF RETURNING ERROR CODES, THE MECHANISM
				USUALLY WASTES 4 BYTES(32BIT), OR 8 BYTES(64BIT), ON THE STACK FOR EACH FUNCTION
				DOEN THE CALL THE STACK. THIS IS EVEN OF THE FIRST LEVEL FUNCTION WAS PASSED A NULL,
				MEANING THE CALLER OF THAT FUNCTION DID NOT WANT TO KNOW ABOUT THE ERROR.
	- TO BE DONE AS PART OF CrxRt MOSTLY. (TODO)
		- A FUNCTION THAT RETURNS AN ERROR SPACE NUMBER FROM A LIBRARY NAME. THIS FUNCTION WILL 
				STILL EMPLOY CrxRt IF IT EXISTS HERE INSTEAD. IF IT EXISTS HERE, THE FUNCTION 
				RETURNS THE GLOBAL ERROR SPACE IF CrxRt IS NOT AVAILABLE.
		- A FUNCTION THAT RETURNS A MESSAGE FROM AN ERROR NUMBER AND ERROR SPACE. THIS FUNCTION WILL 
				STILL EMPLOY CrxRt IF IT EXISTS HERE INSTEAD. IF IT EXISTS HERE, THE FUNCTION 
				RETURNS NULL IF CrxRt IS NOT AVAILABLE.
		- A FUNCTION THAT REGISTERS FUNCTIONS FOR RETURNING MESSAGES GIVEN ERROR CODES. EACH
				LIBRARY, EACH ERROR SPACE, CAN REGISTOR ONE OR NONE SUCH FUNCTIONS. THIS FUNCTION 
				WILL STILL EMPLOY CrxRt IF IT EXISTS HERE INSTEAD. IF IT EXISTS HERE, THE FUNCTION 
				DEOS NOTHING IF CrxRt IS NOT AVAILABLE.
*/
/* USAGE DECISION
	- THERE ARE THREE VALID APPROACHES WHEN REPORTING THE ERROR CODE:
		1- RETURN THE ERROR CODE.
		2- PASS BACK THE ERROR CODE ON A PARAMETER.
		3- EMPLOY ::crx::c::error::Error.
	- IF YOU REQUIRE MULTIPLEXING OR ERROR TRACING, USE THE ::crx::c::error::Error TYPE
			(APPROACH 3).
	- IF YOUR LIBRARY DOES NOT CALL INTO ANOTHER LIBRARY, YOU WOULD NOT REQUIRE MULTIPLEXING. 
	- IF YOUR LIBRARY DOES CALL INTO ANOTHER LIBRARY, AND YOUR LIBRARY IS A FORMAL ABSTRACT SUCH AS 
			THE LIBRARIES IT USES MUST NEVER BE USED BY THE USER CODE, YOUR LIBRARY MIGHT NOT 
			REQUIRE MULTIPLEXING. IN THIS CASE, YOUR LIBRARY IS EITHER COMPLETELY NOT REPORTING THE 
			ERRORS OF THE UNDERLYING LIBRARIES, OR REPORTING THEM MAPPED INTO ITS OWN ERROR CODES
			(APPROACH 1).
	- UNLESS YOUR LIBRARY IS A PROPER ABSTRACT, NEVER EMPLOY MAPPING OF ERROR CODES OF LIBRARIES
			THAT YOUR LIBRARY USES. OTHERWISE, THIS BECOMES TEDIOUS, BECAUSE OTHER LIBRARIES MIGHT
			HAVE TO DO THE SAME WITH SUCH A SCHEME.
	- IF YOU DO NOT REQUIRE MULTIPLEXING NOR ERROR TRACING, BUT REQUIRE THE LOW MEMORY USAGE OF
			THE errorno APPROACH, RETURN YOUR ERROR CODES AS FUNCTION RETURNS. GENERALLY, THESE
			ARE GUARANTEED TO BE RETURNED ON A REGISTER, AND THEREFORE NOT USE MEMORY ON THE 
			STACK (APPROACH 1).

			IF A FUNCTION NEEDS TO RETURN SOMETHING ELSE, YOU SHALL HAVE TO RETURN THE ERROR CODE
			AS A PARAMETER (APPROACH 2).
	- IF YOU NEED MULTIPLEXING, BUT NOT ERROR TRACING, USE ::crx::c::error::Error, BUT MARK IT
			AS SINGULAR. SEE BELOW.
	- WHEN MARKED AS SINGULAR, ::crx::c::error::Error WILL NOT USE THE HEAP, UNLESS THE USER
			PASSES ERRORS THAT USE STRINGS, MEANING ::crx::c::String, OR C STRINGS THAT ARE NOT
			MARKED AS BEING PERSISTANT GLOBAL CONSTANTS.
	- WHEN MARKED AS SINGULAR, ::crx::c::error::Error WILL USE THE LOWEST AMOUNT OF MEMORY POSSIBLE,
			BUT STILL BE MORE EXPENSIVE ON THE STACK THAN SIMPLY RETURNING AN ERROR CODE. ON THE 
			HEAP, IT SHOULD USE NO MEMORY AT ALL, UNLESS THE ORIGINAL CALLER ALLOCATES THE ERROR
			OBJECT ON THE HEAP WHICH IS DISCOURAGED.
*/
	
CRX__LIB__C_CODE_BEGIN()

#if(defined(CRX__LAN__C_99) || defined(UINT32_MAX))
	#define CRX__C__ERROR__PRIVATE__SIZE_T uint16_t
	#define CRX__C__ERROR__PRIVATE__SIZE_MAX UINT16_MAX
#else
	#define CRX__C__ERROR__PRIVATE__SIZE_T size_t
	#ifdef SIZE_MAX
		#define CRX__C__ERROR__PRIVATE__SIZE_MAX SIZE_MAX
	#else
		#define CRX__C__ERROR__PRIVATE__SIZE_MAX ((size_t)(-1))
	#endif
#endif

#define CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET				0
#define CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING  1
#define CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING 	2
#define CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL	3

#define CRX__C__ERROR__MODE__TRACE					0
#define CRX__C__ERROR__MODE__SINGULAR					1
#define CRX__C__ERROR__MODE__SINGULAR_AND_NO_HEAP		2

/*CLASS: ErrorElement*/
typedef struct Crx_C_Error_ErrorElement
{
	CRX_FRIEND_CLASS(Crx_C_Error_Error);

	uint8_t gPrivate_internalMode; 	//0: unset   1: set and using CString   2: set and using string
	uint16_t gSpace;		//0: unnamed 1: system
	uint32_t gCode;
	union 
	{
		void * _gFiller;
		char const * CRX_NOT_MINE gCString; //IF MODE IS 2, THIS IS NEVER NULL
		Crx_C_String * gString;
	}uPrivate_string;
}Crx_C_Error_ErrorElement;


CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct(
		Crx_C_Error_ErrorElement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct2(
		Crx_C_Error_ErrorElement * pThis, uint32_t pCode, 
		Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct3(
		Crx_C_Error_ErrorElement * pThis, uint32_t pCode, char const * pCString, 
		bool pIsCStringAPermanentConstant);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct4(
		Crx_C_Error_ErrorElement * pThis, uint32_t pCode, 
		char const * pChars, size_t pLength);
//WARNING: pString MUST BE NULL CHARACTER TERMINATED AS THE NULL CHARACTER IS DEFINED IN 
//		::crx::c::String, WHICH IS 4 BYTES.
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_error_errorElement_private_takeStringAndConstruct(
		Crx_C_Error_ErrorElement * pThis, uint16_t pSpace, uint32_t pCode, 
		Crx_C_String * pString);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_error_errorElement_private_takeCStringAndConstruct(
		Crx_C_Error_ErrorElement * pThis, uint16_t pSpace, uint32_t pCode, char const * pCString);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_copyConstruct(
		Crx_C_Error_ErrorElement * pThis, Crx_C_Error_ErrorElement const * pErrorElement);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new2(
		uint32_t pCode, Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new3(
		uint32_t pCode, char const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new4(
		uint32_t pCode, char const * pChars, size_t pLength);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Error * crx_c_error_errorElement_moveNew(
		Crx_C_Error_ErrorElement * CRX_NOT_NULL pErrorElement);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_copyNew(
		Crx_C_Error_ErrorElement const * CRX_NOT_NULL pErrorElement);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_destruct(
		Crx_C_Error_ErrorElement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_free(Crx_C_Error_ErrorElement * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_error_errorElement_getMessage(
		Crx_C_Error_ErrorElement const * pThis);

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_error_errorElement_private_unsafeUnsetMessage(
		Crx_C_Error_ErrorElement * pThis);

		
		
/*CLASS: Error*/
/*CRX__C__Array__DECLARE(Crx_C_Error_Error, crx_c_error_error_, Crx_C_Error_ErrorElement, 
		CRX__C__ERROR__PRIVATE__SIZE_T, CRX__C__ERROR__PRIVATE__SIZE_MAX, 
		0, CRXM__FALSE,
		crx_c_error_errorElement_destruct, crx_c_error_errorElement_copyConstruct, CRXM__FALSE, CRXM__FALSE)*/
typedef Crx_C_Error_Error
{
	CRX_FRIEND_CLASS(Crx_C_Error_Iterator)

	uint8_t gPrivate_internalMode;	//0: unset   1:set and using CString   2: set and using String   
									//3: set and using trail.
	//bool gPrivate_isSingular;
	uint8_t gPrivate_mode; //0: With trace   1: Singular(no trace)   
							//2: Singular(no trace) and no heap.
	uint16_t gPrivate_space;	//0: unnamed 1: system
	int32_t gPrivate_code;
	union
	{
		char const * CRX_NOT_MINE gCString;
		Crx_C_String * gString;
		Crx_C_Error_Error_Private_Trail * gTrail; //IF MODE IS 3, THIS IS NEVER NULL
	}uPrivate_data;
}


CRX__C__Queue__DECLARE(Crx_C_Error_Error_Private_Trail, crx_c_error_error_private_trail_,
		CRX__C__QUEUE__MODE__BIDIRECTIONAL, 8, CRXM__FALSE,
		Crx_C_Error_ErrorElement, crx_c_error_errorElement_destruct,
		crx_c_error_errorElement_copyConstruct,
		CRXM__FALSE, CRXM__FALSE)

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_construct(
		Crx_C_Error_Error * pThis, uint32_t pOperationMode);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_copyConstruct(
		Crx_C_Error_Error * pThis, Crx_C_Error_Error const * pError);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Error * crx_c_error_new(uint32_t pOperationMode);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Error * crx_c_error_errorElement_moveNew(
		Crx_C_Error_Error * pError);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Error * crx_c_error_errorElement_copyNew(
		Crx_C_Error_Error const * pError);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_error_error_isError(Crx_C_Error_Error * pThis);
/*
	THE FOLLOWING WILL ATTEMPT TO PREPARE THE TRAIL IF IT IS NOT ALREADY PREPARED. 
	IF THE TRAIL IS NOT ALREADY PREAPRED, AND THE FOLLOWING SUCCEEDS IN PREPARING, IT WILL COPY
			OVER THE ERROR ENTRY THAT MIGHT ALREADY EXIST IN THE STRUCTURE. HENCE, IF THIS
			FUNCTION FAILS, A FALLBACK ERROR ENTRY IN THE STRUCTURE MIGHT STILL EXISTS. IF THE
			FUNCTION SUCCEEDED, THE TRAIL IS GUARANTEED TO BE AVAILABLE, AND IF THE FALLBACK
			ERROR ENTRY EXISTED, TO HAVE ALREADY BEEN COPIED OVER TO THE TRAIL.
*/
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_error_error_private_prepareTrace(
		Crx_C_Error_Error * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_pushTrace2(Crx_C_Error_Error * pThis, 
		uint32_t pCode, Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_pushTrace3(Crx_C_Error_Error * pThis, 
		uint32_t pCode, char const * pCString, bool pIsCStringAPermanentConstant);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_pushTrace4(Crx_C_Error_Error * pThis, 
		uint32_t pCode, char const * pChars, size_t pLength);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_clear(Crx_C_Error_Error * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() uint16_t crx_c_error_error_getSpaceId(Crx_C_Error_Error * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() int32_t crx_c_error_error_getCode(Crx_C_Error_Error * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_error_error_getMessage(Crx_C_Error_Error * pThis);



typedef Crx_C_Error_Iterator
{
	bool gPrivate_internalMode; //0: First from front   1: First from back   2: done
	bool gPrivate_isConstant;
	Crx_C_Error_Error * CRX_NOT_MINE gPrivate_error;
	Crx_C_Error_Error_Private_Trail_Iterator gPrivate_iterator;
}Crx_C_Error_Iterator;


CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_construct(Crx_C_Error_Iterator * pThis,
		Crx_C_Error_Error * pError);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_construct2(Crx_C_Error_Iterator * pThis,
		Crx_C_Error_Error const * pError);
CRX__LIB__PRIVATE_C_FUNCTION() void _crx_c_error_iterator_construct(Crx_C_Error_Iterator * pThis,
		bool pIsConstant, Crx_C_Error_Error * pError);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Iterator * crx_c_error_iterator_new(
		Crx_C_Error_Error * pError);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Iterator * crx_c_error_iterator_new2(
		Crx_C_Error_Error const * pError);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Iterator * Crx_C_Error_iterator_moveNew(
		Crx_C_Error_Iterator * pIterator);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Iterator * Crx_C_Error_iterator_copyNew(
		Crx_C_Error_Iterator const * pIterator);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_free(Crx_C_Error_Iterator * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_associateWith(Crx_C_Error_Iterator * pThis,
		Crx_C_Error_Error * pError);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_constantAssociateWith(
		Crx_C_Error_Iterator * pThis, bool pIsConstant,
		Crx_C_Error_Error const * pError);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_error_iterator_private_doAssociateWith(
		Crx_C_Error_Iterator * pThis, Crx_C_Error_Error const * pError);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_reset(Crx_C_Error_Iterator * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_resetToBack(
		Crx_C_Error_Iterator * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_next(Crx_C_Error_Iterator * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_prev(Crx_C_Error_Iterator * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_error_iterator_isValid(Crx_C_Error_Iterator * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() uint16_t crx_c_error_iterator_getSpaceId(
		Crx_C_Error_Iterator * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() int32_t crx_c_error_iterator_getCode(Crx_C_Error_Iterator * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_error_iterator_getMessage(
		Crx_C_Error_Iterator * pThis);
			
CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/error.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif