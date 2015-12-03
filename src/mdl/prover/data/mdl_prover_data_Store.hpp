/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_data_Store.hpp                                */
/* Description:     store of the tree statistics data                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_DATA_STORE_HPP_
#define MDL_PROVER_DATA_STORE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

#include "mdl/prover/data/mdl_prover_data_Down.hpp"
#include "mdl/prover/data/mdl_prover_data_Root.hpp"
#include "mdl/prover/data/mdl_prover_data_Up.hpp"

namespace mdl {
namespace prover {
namespace data {

class Store :
	public object :: Object,
	public Scalar<Store, allocator :: Heap> {
public :
	Store ();
	virtual ~ Store();

	void add (Data*);

	void showVolume (String&, const int indent = 0) const;
	void showTiming (String&, const int indent = 0) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_DATA_VECTOR_CAPACITY = 64
	};
	typedef
		vector :: Vector
		<
			Data,
			storage :: ByPointer,
			allocator :: Heap
		>
		DataVector_;

	DataVector_ dataVector_;
};

}
}
}

#endif /*MDL_PROVER_DATA_STORE_HPP_*/
