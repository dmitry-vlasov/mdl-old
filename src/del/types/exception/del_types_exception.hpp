/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_exception.hpp                                  */
/* Description:     basic exceptions                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace exception {

	using nstd :: memory :: exception :: OutOfMemory;

	class OutOfTime : public std :: exception {
	};
}
}


