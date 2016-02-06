/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_data_Up.hpp                                   */
/* Description:     prover up tree statistics data                           */
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

class Up :
	public object :: Object,
	public Scalar<Up, allocator :: Heap> {
public :
	Up();
	template<class A>
	Up (const tree :: up :: Tree<A>&);
	virtual ~ Up();

	void operator += (const Up&);
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
	void collectStatistics (const tree :: up :: Tree<A>&);
	void showStatistics (String&, const int indent = 0) const;

	Size_t totalVolume_;

	Size_t crownVolume_;
	Size_t levelVectorVolume_;
	Size_t nodeSetVolume_;
	Size_t nodeVectorVolume_;
	Size_t nodeSproutVolume_;

	int levelVectorSize_;
	int nodeSetSize_;
	int nodeVectorSize_;
	int nodeSproutSize_;

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


