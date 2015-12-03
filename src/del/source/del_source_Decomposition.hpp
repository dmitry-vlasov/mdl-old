/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Decomposition.hpp                             */
/* Description:     solution                                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_DECOMPOSITION_HPP_
#define DEL_SOURCE_DECOMPOSITION_HPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace source {

class Decomposition :
	public del :: Decomposition,
	public Scalar<Decomposition> {
public :
	Decomposition
	(
		const Location&,
		const del :: Comments* const,
		const value :: Theory,
		const value :: Signature,
		const vector :: value :: Symbol&,
		const bool
	);
	Decomposition
	(
		const value :: Theory,
		const value :: Signature,
		const bool
	);
	virtual ~ Decomposition();

	// del :: Decomposition interface
	virtual bool verify() const;
	virtual void addComponent (const value :: Symbol);
	virtual bool isEqual (const del :: Decomposition*) const;
	virtual value :: Integer getSize() const;
	virtual value :: Symbol getComponent (const value :: Integer) const;
	virtual void replicateCompletely (String&) const;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	bool isEqualTheoryDecomposition (const Decomposition*) const;
	bool isEqualSignatureDecomposition (const Decomposition*) const;

	const Location location_;
	const del :: Comments* comments_;
	const value :: Theory theoryName_;
	const value :: Signature signatureName_;
	const del :: Theory* theory_;
	const del :: Signature* signature_;
	vector :: value :: Symbol components_;
	const bool isStrong_;
	enum {
		INITIAL_COMPONENTS_CAPACITY = 16
	};
};

}
}

#endif /*DEL_SOURCE_DECOMPOSITION_HPP_*/
