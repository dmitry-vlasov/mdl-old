/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_statistics_Statistics.hpp                  */
/* Description:     statistics representation                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace auxiliary {
namespace statistics {

class Statistics :
	public nstd :: Object,
	public Scalar<Statistics, allocator :: Heap> {
public :
	enum Kind_ {
		NODE_FORKING             = 0,
		SUBSTITUTION_COMPLEXITY  = 1,
		EXPRESSION_COMPLEXITY    = 2,
		DIMENSION                = 3
	};

	Statistics ();
	virtual ~ Statistics();

	Sample& get (const Kind_);
	const Sample& get (const Kind_) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	Sample data_ [DIMENSION];
};

}
}
}


