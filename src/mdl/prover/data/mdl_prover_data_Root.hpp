/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_data_Root.hpp                                 */
/* Description:     prover root statistics data                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace data {

class Root :
	public object :: Object,
	public Scalar<Root, allocator :: Heap> {
public :
	Root();
	template<class A>
	Root (const tree :: Root<A>&);
	virtual ~ Root();

	void operator += (const Root&);
	void operator /= (const int);

	void showVolume (String&, const int indent = 0) const;
	void showTiming (String&, const int indent = 0) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class A>
	void collectStatistics (const tree :: Root<A>&);
	void showStatistics (String&, const int indent = 0) const;

	Size_t totalVolume_;
	Size_t bufferVolume_;
	Size_t rootVectorVolume_;
	Size_t proofVectorVolume_;
	Size_t stepVectorVolume_;

	int hypCount_;
	int propCount_;
	int refCount_;
	int topCount_;

	Size_t hypVolume_;
	Size_t propVolume_;
	Size_t refVolume_;
	Size_t topVolume_;
};

}
}
}


