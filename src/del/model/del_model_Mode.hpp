/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_Mode.hpp                                       */
/* Description:     mode of the presentation of models                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace model {

class Mode : public del :: Mode {
public :
	enum {
		SHOW_INVERSE  = 0,
		SHOW_NODES    = 1,
		MAX_BIT = SHOW_NODES
	};

	Mode ();
	Mode (const String&);
	Mode (const Mode&);
};

}
}


