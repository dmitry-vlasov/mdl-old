/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Math.ipp                                        */
/* Description:     static container for global del structures               */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline Theories*
	Math :: theories() {
		return theories_;
	}
	inline Signatures*
	Math :: signatures() {
		return signatures_;
	}
	inline Source*
	Math :: source() {
		return source_;
	}
	inline void
	Math :: release()
	{
		deleteAggregateObject (theories_);
		deleteAggregateObject (signatures_);
		deleteAggregateObject (source_);
	}
}
}


