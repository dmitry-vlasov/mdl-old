/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Mode.hpp                                  */
/* Description:     class for the expression show mode                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {

class Mode : public mdl :: Mode {
public :
	enum {
		SHOW_WRITE,
		SHOW_SYMBOL,
		SHOW_HEADER,
		SHOW_TYPE,
		SHOW_TERMS,
		SHOW_TREE,
		SHOW_KIND,
		SHOW_REPLACEABILITY,
		SHOW_SUBSTITUTION,
		MAX_BIT = SHOW_SUBSTITUTION
	};

	Mode ();
	Mode (const String&);
	Mode (const Mode&);
};

}
}


