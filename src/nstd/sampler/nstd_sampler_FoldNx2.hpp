/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_sampler_FoldNx2.hpp                                 */
/* Description:     fold N x 2 sample generator                              */
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
class FoldNx2 :
	public Object,
	public memory :: storage :: Scalar<FoldNx2<A>, A> {
public :
	typedef A Allocator_;
	typedef Sample<Allocator_> Sample_;
	enum {
		DEFAULT_N = 5
	};

	FoldNx2
	(
		Sample_& sample,
		const Integer n = DEFAULT_N
	);
	virtual ~ FoldNx2();

	bool generate (const Integer learningAtLeast);
	void reset();
	Integer getCount() const;
	Integer getIterations() const;
	Integer getIterations (const Integer) const;
	Real getLearningSize() const;

	template<class S>
	void show (S&) const;

	// Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	void generateFold2 (const int k, const bool includeSide);

	const Integer size_;
	const Integer n_;
	Sample_& sample_;

	Integer countFolds_;
	Integer countIterations_;
	bool side_;
};

}
}


