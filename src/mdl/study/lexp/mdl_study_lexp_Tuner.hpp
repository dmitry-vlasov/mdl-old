/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Tuner.hpp                                 */
/* Description:     tuner for the learning algorithms                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_LEXP_TUNER_HPP_
#define MDL_STUDY_LEXP_TUNER_HPP_

namespace mdl {
namespace study {
namespace lexp {

class Tuner :
	public object :: Object,
	public Scalar<Tuner> {
public :
	typedef
		form :: evaluation :: lexp :: Fris<allocator :: Heap>
		Fris_;

	Tuner
	(
		statement :: Experience*,
		const value :: Real percent,
		Format* format = NULL
	);
	virtual ~ Tuner ();

	value :: Real tune (const value :: Real threshold);
	static value :: Real estimateTime
	(
		const value :: Integer size,
		const value :: Real threshold
	);
	const Matrix* getMatrix() const;

	static void init();
	static void release();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		allocator :: Heap
		Allocator_;
	typedef
		sampler :: Sample<Allocator_>
		Sample_;
	typedef
		sampler :: Sampler<Allocator_>
		Sampler_;

	Format* format_;
	statement :: Experience* experience_;

	Matrix* matrix_;
	Stolp*  stolp_;
	const value :: Integer size_;
};

}
}
}

#endif /*MDL_STUDY_LEXP_TUNER_HPP_*/
