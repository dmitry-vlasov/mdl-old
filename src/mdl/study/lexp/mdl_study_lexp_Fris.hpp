/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Fris.hpp                                  */
/* Description:     FRiS function                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace study {
namespace lexp {

class Fris :
	public object :: Object,
	public Scalar<Fris> {
public :
	typedef
		form :: evaluation :: lexp :: template Point<allocator :: Heap>
		Point_;

	Fris (const Matrix*);
	virtual ~ Fris();

	bool classify
	(
		const value :: Integer, // x index
		const Sample& positve,  // positive etalons
		const Sample& negative  // negative etalons
	) const;
	bool classify
	(
		const value :: Integer, // x index
		value :: Real&,         // FRiS value
		const Sample& positve,  // positive etalons
		const Sample& negative  // negative etalons
	) const;

	value :: Real evalSum (const Sample&) const;
	value :: Real eval
	(
		const value :: Integer, // x index
		const Sample&           // current sample
	) const;
	value :: Real eval
	(
		const value :: Integer, // x index
		const value :: Integer, // y index
		const Sample&           // current sample
	) const;
	value :: Real eval
	(
		const value :: Integer i, // u index
		const value :: Integer j, // x index
		const value :: Integer k  // x' index
	) const;
	value :: Real evalWithNearestNeibour
	(
		const value :: Integer i, // u index
		const value :: Integer j, // x index
		const Sample& sample      // current sample
	) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	value :: Real evalAverageDistance
	(
		const bool sign,
		const value :: Integer i, // point index
		const Sample& sample      // current sample
	) const;
	void showFRiS (const Sample& sample, String& string) const;

	const Matrix* matrix_;
};

}
}
}


