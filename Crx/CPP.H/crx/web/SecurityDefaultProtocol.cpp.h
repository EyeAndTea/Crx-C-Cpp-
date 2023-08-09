//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .cpp FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE.
#include "Crx/H/crx/web/SecurityDefaultProtocol.h"

#include "Crx/H/crx/ClassUnorderedMap.h"
#include "Crx/H/crx/Var.h"
#include "Crx/H/crx/web/SecurityProtocol.h"
#include "Crx/H/crx/web/Security.h"
//<<END>>


namespace crx{namespace web
{

	#pragma region CLASS SecurityDefaultProtocol //{

	CRX_PUBLIC SecurityDefaultProtocol::SecurityDefaultProtocol(bool pIsComplexMode CRX_DEFAULT(false)) :
			SecurityProtocol(pIsComplexMode)
	{
		if(this->gDefaultImplementation_htmlFilterData.isNull())
		{
			//CRXSecurityDefaultImplementationVariables::getHtmlFilterVariables();

			//this->gDefaultImplementation_htmlFilterData['a'] = true;

#ifndef CRX__BOOST_NO_CXX11_HDR_INITIALIZER_LIST
			this->gDefaultImplementation_htmlFilterData = ::crx::VarThreadPossible
			{
				{"address", {{}}},
				{"a",
				{
					/*//{"href", true},*/
					{"rel", true},
					{"rev", true},
					{"name", true},
					{"target", true},
				}},
				{"abbr", {{}}},
				{"acronym", {{}}},
				{"area",
				{
					{"alt", true},
					{"coords", true},
					/*//{"href", true},*/
					{"nohref", true},
					{"shape", true},
					{"target", true},
				}},
				{"article",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"aside",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"b", {{}}},
				{"big", {{}}},
				{"blockquote",
				{
					{"cite", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"br", {{}}},
				{"button",
				{
					{"disabled", true},
					{"name", true},
					{"type", true},
					{"value", true},
				}},
				{"caption",
				{
					{"align", true},
				}},
				{"cite",
				{
					{"dir", true},
					{"lang", true},
				}},
				{"code", {{}}},
				{"col",
				{
					{"align", true},
					{"char", true},
					{"charoff", true},
					{"span", true},
					{"dir", true},
					{"valign", true},
					{"width", true},
				}},
				{"colgroup",
				{
					{"align", true},
					{"span", true},
					{"width", true},
				}},
				{"del",
				{
					{"datetime", true},
				}},
				{"dd", {{}}},
				{"dfn", {{}}},
				{"details",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					{"open", true},
					/*//{"xml:lang", true},*/
				}},
				{"div",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"dl", {{}}},
				{"dt", {{}}},
				{"em", {{}}},
				{"fieldset", {{}}},
				{"figure",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"figcaption",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				/*// {"font",
				// {
					// {"color", true},
					// {"face", true},
					// {"size", true},
				// }},*/
				{"footer",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				/*// {"form", 
				// {
					// {"action", true},
					// {"accept", true},
					// {"accept-charset", true},
					// {"enctype", true},
					// {"method", true},
					// {"name", true},
					// {"target", true},
				// }},*/
				{"h1",
				{
					{"align", true},
				}},
				{"h2",
				{
					{"align", true},
				}},
				{"h3",
				{
					{"align", true},
				}},
				{"h4",
				{
					{"align", true},
				}},
				{"h5",
				{
					{"align", true},
				}},
				{"h6",
				{
					{"align", true},
				}},
				{"header",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"hgroup",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"hr",
				{
					{"align", true},
					{"noshade", true},
					{"size", true},
					{"width", true},
				}},
				{"i", {{}}},
				{"img",
				{
					/*// {"alt", true},
					// {"align", true},
					// {"border", true},
					// {"height", true},
					// {"hspace", true},
					// {"longdesc", true},
					// {"vspace", true},*/
					{"src", true},
					/*// {"usemap", true},
					// {"width", true},*/
				}},
				{"ins",
				{
					{"datetime", true},
					{"cite", true},
				}},
				{"kbd", {{}}},
				{"label",
				{
					{"for", true},
				}},
				{"legend",
				{
					{"align", true},
				}},
				{"li",
				{
					{"align", true},
					{"value", true},
				}},
				{"map",
				{
					{"name", true},
				}},
				{"mark", {{}}},
				{"menu",
				{
					{"type", true},
				}},
				{"nav",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"p",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"pre",
				{
					{"width", true},
				}},
				{"q",
				{
					{"cite", true},
				}},
				{"s", {{}}},
				{"samp", {{}}},
				{"span",
				{
					{"dir", true},
					{"align", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"section",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"small", {{}}},
				{"strike", {{}}},
				{"strong", {{}}},
				{"style", {{}}},		
				{"sub", {{}}},
				{"summary",
				{
					{"align", true},
					{"dir", true},
					{"lang", true},
					/*//{"xml:lang", true},*/
				}},
				{"sup", {{}}},
				{"table",
				{
					{"align", true},
					{"bgcolor", true},
					{"border", true},
					{"cellpadding", true},
					{"cellspacing", true},
					/*//{"dir", true},*/
					{"rules", true},
					{"summary", true},
					{"width", true},
				}},
				{"tbody",
				{
					{"align", true},
					{"char", true},
					{"charoff", true},
					{"valign", true},
				}},
				{"td",
				{
					{"abbr", true},
					{"align", true},
					{"axis", true},
					{"bgcolor", true},
					{"char", true},
					{"charoff", true},
					{"colspan", true},
					{"dir", true},
					{"headers", true},
					{"height", true},
					{"nowrap", true},
					{"rowspan", true},
					/*//{"scope", true},*/
					{"valign", true},
					{"width", true},
				}},
				{"textarea",
				{
					{"cols", true},
					{"rows", true},
					{"disabled", true},
					{"name", true},
					{"readonly", true},
				}},
				{"tfoot",
				{
					{"align", true},
					{"char", true},
					{"charoff", true},
					{"valign", true},
				}},
				{"th",
				{
					{"abbr", true},
					{"align", true},
					{"axis", true},
					{"bgcolor", true},
					{"char", true},
					{"charoff", true},
					{"colspan", true},
					{"headers", true},
					{"height", true},
					{"nowrap", true},
					{"rowspan", true},
					{"scope", true},
					{"valign", true},
					{"width", true},
				}},
				{"thead",
				{
					{"align", true},
					{"char", true},
					{"charoff", true},
					{"valign", true},
				}},
				{"title", {{}}},
				{"tr",
				{
					{"align", true},
					{"bgcolor", true},
					{"char", true},
					{"charoff", true},
					{"valign", true},
				}},
				{"tt", {{}}},
				{"u", {{}}},
				{"ul",
				{
					{"type", true},
				}},
				{"ol",
				{
					{"start", true},
					{"type", true},
				}},
				{"var",{}}
			};

			/*{	
				{{"a", 5},
				{"b",
				{
					{"b1", 3},
					{"b2", 4},
					{{"b3", 4}, true}
				}},
				{{"c", 2}, false},
				{"d", "ffdsfsd"},
				{"e", "ffdsfsd"}}, true
			};*/
			/*{
				true,
				{{true, "a",
				{
					true,
					{{true, "a1", 4},
					{true, "a2", 4}}
				}}}
			};*/
#else
			this->gDefaultImplementation_htmlFilterData = ::crx::Var::parseVarJson(
			"{"
				"`address`: {},"
				"`a`:"
				"{"
					//"/*//`href`: true,*/"
					"`rel`: true,"
					"`rev`: true,"
					"`name`: true,"
					"`target`: true,"
				"},"
				"`abbr`: {},"
				"`acronym`: {},"
				"`area`:"
				"{"
					"`alt`: true,"
					"`coords`: true,"
					//"/*//`href`: true,*/"
					"`nohref`: true,"
					"`shape`: true,"
					"`target`: true,"
				"},"
				"`article`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					//"/*//`xml:lang`: true,*/"
				"},"
				"`aside`:"
				"{"
					"`align`: true:"
					"`dir`: true,"
					"`lang`: true,"
					//"/*//`xml:lang`: true,*/"
				"},"
				"`b`: {},"
				"`big`: {},"
				"`blockquote`:"
				"{"
					"`cite`: true,"
					"`lang`: true,"
					/*//{`xml:lang`, true},*/
				"},"
				"`br`: {},"
				"`button`:"
				"{"
					"`disabled`: true,"
					"`name`: true,"
					"`type`: true,"
					"`value`: true,"
				"},"
				"`caption`:"
				"{"
					"`align`: true,"
				"},"
				"`cite`:"
				"{"
					"`dir`: true,"
					"`lang`: true,"
				"},"
				"`code`: {},"
				"`col`:"
				"{"
					"`align`: true,"
					"`char`: true,"
					"`charoff`: true,"
					"`span`: true,"
					"`dir`: true,"
					"`valign`: true,"
					"`width`: true,"
				"},"
				"`colgroup`:"
				"{"
					"`align`: true,"
					"`span`: true,"
					"`width`: true,"
				"},"
				"`del`:"
				"{"
					"`datetime`: true,"
				"},"
				"`dd`: {},"
				"`dfn`: {},"
				"`details`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					"`open`: true,"
					"/*//{`xml:lang`, true},*/"
				"},"
				"`div`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					"/*//{`xml:lang`, true},*/"
				"},"
				"`dl`: {},"
				"`dt`: {},"
				"`em`: {},"
				"`fieldset`: {},"
				"`figure`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					"/*//{`xml:lang`, true},*/"
				"},"
				"`figcaption`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					"/*//{`xml:lang`, true},*/"
				"},"
				/*// {`font`,"
				"// {"
					"// {`color`, true},"
					"// {`face`, true},"
					"// {`size`, true},"
				"// }},*/
				"`footer`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					/*//{`xml:lang`, true},*/
				"},"
				/*// {`form`," 
				"// {"
					"// {`action`, true},"
					"// {`accept`, true},"
					"// {`accept-charset`, true},"
					"// {`enctype`, true},"
					"// {`method`, true},"
					"// {`name`, true},"
					"// {`target`, true},"
				"// }},*/
				"`h1`:"
				"{"
					"`align`: true,"
				"},"
				"`h2`:"
				"{"
					"`align`: true,"
				"},"
				"`h3`:"
				"{"
					"`align`: true,"
				"},"
				"`h4`:"
				"{"
					"`align`: true,"
				"},"
				"`h5`:"
				"{"
					"`align`: true,"
				"},"
				"`h6`:"
				"{"
					"`align`: true,"
				"},"
				"`header`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					/*//{`xml:lang`, true},*/
				"},"
				"`hgroup`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					/*//{`xml:lang`, true},*/
				"},"
				"`hr`:"
				"{"
					"`align`: true,"
					"`noshade`: true,"
					"`size`: true,"
					"`width`: true,"
				"},"
				"`i`: {},"
				"`img`:"
				"{"
					/*// {`alt`, true},"
					"// {`align`, true},"
					"// {`border`, true},"
					"// {`height`, true},"
					"// {`hspace`, true},"
					"// {`longdesc`, true},"
					"// {`vspace`, true},*/
					"`src`: true,"
					/*// {`usemap`, true},"
					"// {`width`, true},*/
				"},"
				"`ins`:"
				"{"
					"`datetime`: true,"
					"`cite`: true,"
				"},"
				"`kbd`: {},"
				"`label`:"
				"{"
					"`for`: true,"
				"},"
				"`legend`:"
				"{"
					"`align`: true,"
				"},"
				"`li`:"
				"{"
					"`align`: true,"
					"`value`: true,"
				"},"
				"`map`:"
				"{"
					"`name`: true,"
				"},"
				"`mark`: {},"
				"`menu`:"
				"{"
					"`type`: true,"
				"},"
				"`nav`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					/*//{`xml:lang`, true},*/
				"},"
				"`p`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					/*//{`xml:lang`, true},*/
				"},"
				"`pre`:"
				"{"
					"`width`: true,"
				"},"
				"`q`:"
				"{"
					"`cite`: true,"
				"},"
				"`s`: {},"
				"`samp`: {},"
				"`span`:"
				"{"
					"`dir`: true,"
					"`align`: true,"
					"`lang`: true,"
					/*//{`xml:lang`, true},*/
				"},"
				"`section`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					/*//{`xml:lang`, true},*/
				"},"
				"`small`: {},"
				"`strike`: {},"
				"`strong`: {},"
				"`style`: {},"		
				"`sub`: {},"
				"`summary`:"
				"{"
					"`align`: true,"
					"`dir`: true,"
					"`lang`: true,"
					/*//{`xml:lang`, true},*/
				"},"
				"`sup`: {},"
				"`table`:"
				"{"
					"`align`: true,"
					"`bgcolor`: true,"
					"`border`: true,"
					"`cellpadding`: true,"
					"`cellspacing`: true,"
					/*//{`dir`, true},*/
					"`rules`: true,"
					"`summary`: true,"
					"`width`: true,"
				"},"
				"`tbody`:"
				"{"
					"`align`: true,"
					"`char`: true,"
					"`charoff`: true,"
					"`valign`: true,"
				"},"
				"`td`:"
				"{"
					"`abbr`: true,"
					"`align`: true,"
					"`axis`: true,"
					"`bgcolor`: true,"
					"`char`: true,"
					"`charoff`: true,"
					"`colspan`: true,"
					"`dir`: true,"
					"`headers`: true,"
					"`height`: true,"
					"`nowrap`: true,"
					"`rowspan`: true,"
					/*//{`scope`, true},*/
					"`valign`: true,"
					"`width`: true,"
				"},"
				"`textarea`:"
				"{"
					"`cols`: true,"
					"`rows`: true,"
					"`disabled`: true,"
					"`name`: true,"
					"`readonly`: true,"
				"},"
				"`tfoot`:"
				"{"
					"`align`: true,"
					"`char`: true,"
					"`charoff`: true,"
					"`valign`: true,"
				"},"
				"`th`:"
				"{"
					"`abbr`: true,"
					"`align`: true,"
					"`axis`: true,"
					"`bgcolor`: true,"
					"`char`: true,"
					"`charoff`: true,"
					"`colspan`: true,"
					"`headers`: true,"
					"`height`: true,"
					"`nowrap`: true,"
					"`rowspan`: true,"
					"`scope`: true,"
					"`valign`: true,"
					"`width`: true,"
				"},"
				"`thead`:"
				"{"
					"`align`: true,"
					"`char`: true,"
					"`charoff`: true,"
					"`valign`: true,"
				"},"
				"`title`: {},"
				"`tr`:"
				"{"
					"`align`: true,"
					"`bgcolor`: true,"
					"`char`: true,"
					"`charoff`: true,"
					"`valign`: true,"
				"},"
				"`tt`: {},"
				"`u`: {},"
				"`ul`:"
				"{"
					"`type`: true,"
				"},"
				"`ol`:"
				"{"
					"`start`: true,"
					"`type`: true,"
				"},"
				"`var`:{}"
			"}");
#endif
		}
		if(this->gDefaultImplementation_cssFilterData.isNull())
		{
#ifndef CRX__BOOST_NO_CXX11_HDR_INITIALIZER_LIST
			this->gDefaultImplementation_cssFilterData = ::crx::VarThreadPossible
			{
				/*// {"align-content", true},
				// {"align-items", true},
				// {"align-self", true},
				// {"animation", true},
				// {"animation-delay", true},
				// {"animation-direction", true},
				// {"animation-duration", true},
				// {"animation-fill-mode", true},
				// {"animation-iteration-count", true},
				// {"animation-name", true},
				// {"animation-play-state", true},
				// {"animation-timing-function", true},
				// {"backface-visibility", true},
				// {"background", true},
				// {"background-attachment", true},
				// {"background-clip", true},*/
				{"background-color", true},
				{"background-image", true},
				/*// {"background-origin", true},
				// {"background-position", true},
				// {"background-repeat", true},
				// {"background-size", true},*/
				{"border", true},
				{"border-bottom", true},
				{"border-bottom-color", true},
				{"border-bottom-left-radius", true},
				{"border-bottom-right-radius", true},
				{"border-bottom-style", true},
				{"border-bottom-width", true},
				{"border-collapse", true},
				{"border-color", true},
				/*// {"border-image", true},
				// {"border-image-outset", true},
				// {"border-image-repeat", true},
				// {"border-image-slice", true},
				// {"border-image-source", true},
				// {"border-image-width", true},*/
				{"border-left", true},
				{"border-left-color", true},
				{"border-left-style", true},
				{"border-left-width", true},
				{"border-radius", true},
				{"border-right", true},
				{"border-right-color", true},
				{"border-right-style", true},
				{"border-right-width", true},
				{"border-spacing", true},
				{"border-style", true},
				{"border-top", true},
				{"border-top-color", true},
				{"border-top-left-radius", true},
				{"border-top-right-radius", true},
				{"border-top-style", true},
				{"border-top-width", true},
				{"border-width", true},
				{"bottom", true},
				{"box-shadow", true},
				{"box-sizing", true},
				/*// {"caption-side", true},*/
				{"clear", true},
				/*// {"clip", true},*/
				{"color", true},
				/*// {"column-count", true},
				// {"column-fill", true},
				// {"column-gap", true},
				// {"column-rule", true},
				// {"column-rule-color", true},
				// {"column-rule-style", true},
				// {"column-rule-width", true},
				// {"column-span", true},
				// {"column-width", true},
				// {"columns", true},
				// {"content", true},
				// {"counter-increment", true},
				// {"counter-reset", true},
				// {"cursor", true},
				// {"direction", true},*/
				{"display", true},
				/*// {"empty-cells", true},
				// {"flex", true},
				// {"flex-basis", true},
				// {"flex-direction", true},
				// {"flex-flow", true},
				// {"flex-grow", true},
				// {"flex-shrink", true},
				// {"flex-wrap", true},*/
				{"float", true},
				/*// {"font", true},
				// "@font-face" => true,
				// {"font-family", true},*/
				{"font-size", true},
				/*// {"font-size-adjust", true},
				// {"font-stretch", true},
				// {"font-style", true},
				// {"font-variant", true},*/
				{"font-weight", true},
				/*// {"hanging-punctuation", true},*/
				{"height", true},
				/*// {"icon", true},
				// {"justify-content", true},
				// "@keyframes" => true,*/
				{"left", true},
				{"letter-spacing", true},
				{"line-height", true},
				{"list-style", true},
				/*// {"list-style-image", true},*/
				{"list-style-position", true},
				{"list-style-type", true},
				{"margin", true},
				{"margin-bottom", true},
				{"margin-left", true},
				{"margin-right", true},
				{"margin-top", true},
				{"max-height", true},
				{"max-width", true},
				/*// "@media" => true,*/
				{"min-height", true},
				{"min-width", true},
				{"nav-down", true},
				{"nav-index", true},
				{"nav-left", true},
				{"nav-right", true},
				{"nav-up", true},
				{"opacity", true},
				{"order", true},
				{"outline", true},
				{"outline-color", true},
				{"outline-offset", true},
				{"outline-style", true},
				{"outline-width", true},
				{"overflow", true},
				{"overflow-x", true},
				{"overflow-y", true},
				{"padding", true},
				{"padding-bottom", true},
				{"padding-left", true},
				{"padding-right", true},
				{"padding-top", true},
				/*// {"page-break-after", true},
				// {"page-break-before", true},
				// {"page-break-inside", true},
				// {"perspective", true},
				// {"perspective-origin", true},*/
				{"position", true},
				/*// {"quotes", true},*/
				{"resize", true},
				{"right", true},
				/*// {"tab-size", true},*/
				{"table-layout", true},
				{"text-align", true},
				{"text-align-last", true},
				{"text-decoration", true},
				{"text-decoration-color", true},
				{"text-decoration-line", true},
				{"text-decoration-style", true},
				{"text-indent", true},
				{"text-justify", true},
				{"text-overflow", true},
				{"text-shadow", true},
				{"text-transform", true},
				{"top", true},
				/*// {"transform", true},
				// {"transform-origin", true},
				// {"transform-style", true},
				// {"transition", true},
				// {"transition-delay", true},
				// {"transition-duration", true},
				// {"transition-property", true},
				// {"transition-timing-function", true},
				// {"unicode-bidi", true},*/
				{"vertical-align", true},
				{"visibility", true},
				{"white-space", true},
				{"width", true},
				{"word-break", true},
				{"word-spacing", true},
				{"word-wrap", true},
				{"z-index", true}
			};
				
#else
			this->gDefaultImplementation_cssFilterData = ::crx::Var::parseVarJson( //{
			"{"
				/*// {`align-content`: true},
				// {`align-items`: true},
				// {`align-self`: true},
				// {`animation`: true},
				// {`animation-delay`: true},
				// {`animation-direction`: true},
				// {`animation-duration`: true},
				// {`animation-fill-mode`: true},
				// {`animation-iteration-count`: true},
				// {`animation-name`: true},
				// {`animation-play-state`: true},
				// {`animation-timing-function`: true},
				// {`backface-visibility`: true},
				// {`background`: true},
				// {`background-attachment`: true},
				// {`background-clip`: true},*/
				"`background-color`: true,"
				"`background-image`: true,"
				/*// {`background-origin`: true},
				// {`background-position`: true},
				// {`background-repeat`: true},
				// {`background-size`: true},*/
				"`border`: true,"
				"`border-bottom`: true,"
				"`border-bottom-color`: true,"
				"`border-bottom-left-radius`: true,"
				"`border-bottom-right-radius`: true,"
				"`border-bottom-style`: true,"
				"`border-bottom-width`: true,"
				"`border-collapse`: true,"
				"`border-color`: true,"
				/*// {`border-image`: true},
				// {`border-image-outset`: true},
				// {`border-image-repeat`: true},
				// {`border-image-slice`: true},
				// {`border-image-source`: true},
				// {`border-image-width`: true},*/
				"`border-left`: true,"
				"`border-left-color`: true,"
				"`border-left-style`: true,"
				"`border-left-width`: true,"
				"`border-radius`: true,"
				"`border-right`: true,"
				"`border-right-color`: true,"
				"`border-right-style`: true,"
				"`border-right-width`: true,"
				"`border-spacing`: true,"
				"`border-style`: true,"
				"`border-top`: true,"
				"`border-top-color`: true,"
				"`border-top-left-radius`: true,"
				"`border-top-right-radius`: true,"
				"`border-top-style`: true,"
				"`border-top-width`: true,"
				"`border-width`: true,"
				"`bottom`: true,"
				"`box-shadow`: true,"
				"`box-sizing`: true,"
				/*// {`caption-side`: true},*/
				"`clear`: true,"
				/*// {`clip`: true},*/
				"`color`: true,"
				/*// {`column-count`: true},
				// {`column-fill`: true},
				// {`column-gap`: true},
				// {`column-rule`: true},
				// {`column-rule-color`: true},
				// {`column-rule-style`: true},
				// {`column-rule-width`: true},
				// {`column-span`: true},
				// {`column-width`: true},
				// {`columns`: true},
				// {`content`: true},
				// {`counter-increment`: true},
				// {`counter-reset`: true},
				// {`cursor`: true},
				// {`direction`: true},*/
				"`display`: true,"
				/*// {`empty-cells`: true},
				// {`flex`: true},
				// {`flex-basis`: true},
				// {`flex-direction`: true},
				// {`flex-flow`: true},
				// {`flex-grow`: true},
				// {`flex-shrink`: true},
				// {`flex-wrap`: true},*/
				"`float`: true,"
				/*// {`font`: true},
				// `@font-face` => true,
				// {`font-family`: true},*/
				"`font-size`: true,"
				/*// {`font-size-adjust`: true},
				// {`font-stretch`: true},
				// {`font-style`: true},
				// {`font-variant`: true},*/
				"`font-weight`: true,"
				/*// {`hanging-punctuation`: true},*/
				"`height`: true,"
				/*// {`icon`: true},
				// {`justify-content`: true},
				// `@keyframes` => true,*/
				"`left`: true,"
				"`letter-spacing`: true,"
				"`line-height`: true,"
				"`list-style`: true,"
				/*// {`list-style-image`: true},*/
				"`list-style-position`: true,"
				"`list-style-type`: true,"
				"`margin`: true,"
				"`margin-bottom`: true,"
				"`margin-left`: true,"
				"`margin-right`: true,"
				"`margin-top`: true,"
				"`max-height`: true,"
				"`max-width`: true,"
				/*// `@media` => true,*/
				"`min-height`: true,"
				"`min-width`: true,"
				"`nav-down`: true,"
				"`nav-index`: true,"
				"`nav-left`: true,"
				"`nav-right`: true,"
				"`nav-up`: true,"
				"`opacity`: true,"
				"`order`: true,"
				"`outline`: true,"
				"`outline-color`: true,"
				"`outline-offset`: true,"
				"`outline-style`: true,"
				"`outline-width`: true,"
				"`overflow`: true,"
				"`overflow-x`: true,"
				"`overflow-y`: true,"
				"`padding`: true,"
				"`padding-bottom`: true,"
				"`padding-left`: true,"
				"`padding-right`: true,"
				"`padding-top`: true,"
				/*// {`page-break-after`: true},
				// {`page-break-before`: true},
				// {`page-break-inside`: true},
				// {`perspective`: true},
				// {`perspective-origin`: true},*/
				"`position`: true,"
				/*// {`quotes`: true},*/
				"`resize`: true,"
				"`right`: true,"
				/*// {`tab-size`: true},*/
				"`table-layout`: true,"
				"`text-align`: true,"
				"`text-align-last`: true,"
				"`text-decoration`: true,"
				"`text-decoration-color`: true,"
				"`text-decoration-line`: true,"
				"`text-decoration-style`: true,"
				"`text-indent`: true,"
				"`text-justify`: true,"
				"`text-overflow`: true,"
				"`text-shadow`: true,"
				"`text-transform`: true,"
				"`top`: true,"
				/*// {`transform`: true},
				// {`transform-origin`: true},
				// {`transform-style`: true},
				// {`transition`: true},
				// {`transition-delay`: true},
				// {`transition-duration`: true},
				// {`transition-property`: true},
				// {`transition-timing-function`: true},
				// {`unicode-bidi`: true},*/
				"`vertical-align`: true,"
				"`visibility`: true,"
				"`white-space`: true,"
				"`width`: true,"
				"`word-break`: true,"
				"`word-spacing`: true,"
				"`word-wrap`: true,"
				"`z-index`: true"
			"}"); //}
#endif
			//CRXSecurityDefaultImplementationVariables::getCssFilterVariables();
		}
	}

	CRX_PROTECTED_VIRTUAL bool SecurityDefaultProtocol::doFilterHtmlElement(bool pIsNotComplexMode, 
			Security * CRX_NOT_NULL pCrxSecurity, Security_ElementData * CRX_NOT_NULL pElementData, 
			::pugi::xml_node const & pNode)
	{
		//echo "filterHtmlElement: " + htmlspecialchars($pElementData['name']);
		if(this->gDefaultImplementation_htmlFilterData.hasKey(pElementData->gName))
		{
			if(pElementData->gName == "img")
			{
				pElementData->gMayHasChildElements = false;
				pElementData->gMayHasTextContent = false;
			}
			else if(pElementData->gName == "style")
				{pElementData->gMayHasChildElements = false;}

			return true;
		}

		return false;		
	}
	CRX_PROTECTED_VIRTUAL bool SecurityDefaultProtocol::doFilterHtmlAttributeAndValue(bool pIsNotComplexMode, 
			Security * CRX_NOT_NULL pCrxSecurity, ::std::string const & pElementName, 
			Security_AttributeData * CRX_NOT_NULL pAttributeData)
	{
		//echo "filterHtmlAttributeAndValue: [".htmlspecialchars($pAttributeData['name'])."::".htmlspecialchars($pAttributeData['value'])."]<br/>";
		if(pAttributeData->gName == "style")
		{
			pAttributeData->gValue = pCrxSecurity->processInlineCss(pAttributeData->gValue);

			return true;
		}
		else if(this->gDefaultImplementation_htmlFilterData.hasKey(pElementName) &&
				this->gDefaultImplementation_htmlFilterData[pElementName].hasKey(pAttributeData->gName))
		{
			if(pIsNotComplexMode)
			{
				if((pAttributeData->gName == "href") ||
						(pAttributeData->gName == "src"))
					{pAttributeData->gValue = pCrxSecurity->sanitizeUrlForHtmlAttribute(pAttributeData->gValue);}
			}

			return true;
		}
		else
			{return false;}
	}
	CRX_PROTECTED_VIRTUAL ::std::string SecurityDefaultProtocol::doSieveHtmlElementText(bool pIsNotComplexMode, 
			Security * CRX_NOT_NULL pCrxSecurity, ::std::string const & pElementName,
			::std::string const & pText, bool pIsCDATA)
	{
		if(pElementName == "style")
		{
			char const * tSearches[] = {"]]>", "<", ""};

			if(pIsNotComplexMode)
			{
				/*
					<script type="text/javascript">
						<!--//--><![CDATA[//><!--
							......
						//--><!]]>
					</script>
				*/
				//
				//	<style type="text/css">
				//		<!--/*--><![CDATA[/*><!-- */
				//			......
				//		/*]]>*/-->
				//	</style>
				
				
				//    <!--//--><![CDATA[//><!--
				// 		//--><!]]>
				//return $pCrxSecurity->cageHtmlText($pCrxSecurity->processCSS($pText));
				return ::std::string("<!--/*--><![CDATA[/*><!--*/\n") + pCrxSecurity->cpp_removeSubstringsIgnoringCaseFrom(
						pCrxSecurity->processCss(pText), tSearches) + "\n/*]]>*/-->";
			}
			else
			{
				return pCrxSecurity->cpp_removeSubstringsIgnoringCaseFrom(pCrxSecurity->processCss(pText), tSearches);
			}
		}
		else if(pElementName == "script") //NOT EXPECTED TO HAPPEN, BUT ADDED FOR COMPLETENESS
		{
			char const * tSearches[] = {"]]>", "<", ""};

			if(pIsNotComplexMode)
			{
				return ::std::string("<!--//--><![CDATA[//><!--\n") + pCrxSecurity->cpp_removeSubstringsIgnoringCaseFrom(
						pCrxSecurity->processCss(pText), tSearches) + "\n//--><!]]>";
			}
			else
				{return pCrxSecurity->cpp_removeSubstringsIgnoringCaseFrom(pCrxSecurity->processCss(pText), tSearches);}
		}
		else if(pIsCDATA)
			{return "";}
		else
		{
			if(pIsNotComplexMode)
				{return pCrxSecurity->cageHtmlText(pText);}
			else
				{return pText;}
		}
	}

	/*
		REMEMBER THAT IN THE C++ PORT OF THIS PROJECT, WE USE AN ACTUAL CRXCSS PARSER, NOT A CSS PARSER,
		AND HENCE THE DEFAULT PROTOCOL, THIS CLASS, CAN NOT DO PROPER FILTERING OF CSS UNLESS IT PROCEEDS
		TO PARSE THE REMAINING CSS, THAT CSS WITHIN THE CRXCSS UNITS, ITSELF. HENCE UNTILL THEN
		THE FUNCTIONS SIMPLY REJECT EVERYTHING.
	*/
	CRX_PROTECTED_VIRTUAL bool SecurityDefaultProtocol::doFilterCrxCssAtRuleElement(bool pIsNotComplexMode, 
			Security * CRX_NOT_NULL pSecurity, 
			Security_CrxCssAtRuleElementData * CRX_NOT_NULL pCrxCssAtRuleElementData)
		{return false;}
	CRX_PROTECTED_VIRTUAL bool SecurityDefaultProtocol::doFilterCrxCssAtRuleStatement(bool pIsNotComplexMode, 
			Security * CRX_NOT_NULL pSecurity, 
			Security_CrxCssAtRuleStatementData * CRX_NOT_NULL pCrxCssAtRuleStatementData)
		{return false;}
	CRX_PROTECTED_VIRTUAL bool SecurityDefaultProtocol::doFilterCrxCssAtRuleNameValueBlock(bool pIsNotComplexMode, 
			Security * CRX_NOT_NULL pSecurity, 
			Security_CrxCssAtRuleNameValueBlockData * CRX_NOT_NULL pCrxCssAtRuleNameValueBlockData)
		{return false;}
	CRX_PROTECTED_VIRTUAL bool SecurityDefaultProtocol::doFilterCrxCssNameValuePair(bool pIsNotComplexMode, 
			Security * CRX_NOT_NULL pSecurity, 
			Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
			::std::string const & pAtRuleName, ::std::string const & pAtRuleValue)
		{return false;}
	CRX_PROTECTED_VIRTUAL bool SecurityDefaultProtocol::doFilterCrxCssNameValuePair2(bool pIsNotComplexMode, 
			Security * CRX_NOT_NULL pSecurity, 
			Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
			::std::vector<Security_CrxCssReference> const & pReferences)
		{return false;}
	CRX_PROTECTED_VIRTUAL bool SecurityDefaultProtocol::doFilterCrxCssReferenceNameValueBlock(bool pIsNotComplexMode, 
			Security * CRX_NOT_NULL pSecurity,
			Security_CrxCssReferenceNameValueBlockData * CRX_NOT_NULL pCrxCssReferenceNameValueBlockData)
		{return false;}

	#pragma endregion CLASS SecurityDefaultProtocol //}
}}

