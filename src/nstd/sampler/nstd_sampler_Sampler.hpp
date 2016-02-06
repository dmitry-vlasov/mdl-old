/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_sampler_Sampler.hpp                                 */
/* Description:     sample generator                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace sampler {

template<class A>
class Sampler :
	public Object,
	public memory :: storage :: Scalar<Sampler<A>, A> {
public :
	typedef A Allocator_;
	typedef Sample<Allocator_> Sample_;

	enum Mode_ {
		LEAVE_ONE_OUT_MODE,
		FOLD_NX2_MODE,
		//DEFAULT_MODE = LEAVE_ONE_OUT_MODE
		DEFAULT_MODE = FOLD_NX2_MODE
	};

	Sampler
	(
		const Integer size,
		const Mode_ = DEFAULT_MODE
	);
	virtual ~ Sampler();

	bool generate (const Integer learningAtLeast = Undefined<Integer> :: getValue());
	Integer getCount() const;
	Integer getIterations() const;
	Integer getIterations(const Integer) const;
	Real getLearningSize() const;
	Sample_& getSample();
	void reset();

	template<class S>
	void show (S&) const;

	// Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	typedef
		LeaveOneOut<Allocator_>
		LeaveOneOut_;
	typedef
		FoldNx2<Allocator_>
		FoldNx2_;

	const Mode_ mode_;
	const Integer size_;
	Sample_ sample_;

	LeaveOneOut_* leaveOneOut_;
	FoldNx2_*     foldNx2_;
};

}
}


