/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_Mode.cpp                                       */
/* Description:     mode of the presentation of models                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_MODE_CPP_
#define DEL_MODEL_MODE_CPP_

namespace del {
namespace model {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Mode :: Mode () :
	del :: Mode () {
	}
	inline
	Mode :: Mode (const String& string) :
	del :: Mode (string) {
	}
	inline
	Mode :: Mode (const Mode& mode) :
	del :: Mode (mode) {
	}
}
}

#endif /*DEL_MODEL_MODE_CPP_*/
