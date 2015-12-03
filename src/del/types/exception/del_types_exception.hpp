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

#ifndef DEL_TYPES_EXCEPTION_HPP_
#define DEL_TYPES_EXCEPTION_HPP_

namespace del {
namespace exception {

	using nstd :: memory :: exception :: OutOfMemory;

	class OutOfTime : public std :: exception {
	};
}
}

#endif /*DEL_TYPES_EXCEPTION_HPP_*/
