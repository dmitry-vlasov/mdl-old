/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_data_Down.hpp                                 */
/* Description:     prover down tree statistics data                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_DATA_DOWN_HPP_
#define MDL_PROVER_DATA_DOWN_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace data {

class Down :
	public object :: Object,
	public Scalar<Down, allocator :: Heap> {
public :
	Down();
	template<class A>
	Down (const tree :: down :: Tree<A>&);
	virtual ~ Down();

	void operator += (const Down&);
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
	void collectStatistics (const tree :: down :: Tree<A>&);
	void showStatistics (String&, const int indent = 0) const;

	Size_t totalVolume_;

	Size_t crownVolume_;
	Size_t levelVectorVolume_;
	Size_t evidenceVectorVolume_;
	Size_t unusedVectorVolume_;

	int levelVectorSize_;
	int evidenceVectorSize_;
	int unusedVectorSize_;

	int hypCount_;
	int propCount_;
	int refCount_;
	int subCount_;
	int topCount_;

	Size_t hypVolume_;
	Size_t propVolume_;
	Size_t refVolume_;
	Size_t subVolume_;
	Size_t topVolume_;
};

}
}
}

#endif /*MDL_PROVER_DATA_DOWN_HPP_*/
