/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Sample_1.hpp                          */
/* Description:     1 dim. sample for the polynomial interpolation           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "nstd/sampler/nstd_sampler_Sample.hpp"

namespace nstd {
namespace interpolation {

template<class A>
class Sample<1, A> :
	public Object,
	public memory :: storage :: Scalar<Sample<1, A>, A> {
public :
	typedef A Allocator_;
	typedef
		typename sampler :: Sample<Allocator_>
		Sample_;
	typedef
		typename Sample_ :: Mode_
		Mode_;
	typedef
		typename container :: Vector
		<
			Real,
			container :: storage :: ByValue,
			Allocator_
		>
		RealVector_;

	Sample
	(
		const RealVector_& xVector,
		const RealVector_& yVector
	);
	Sample (const Sample&);
	virtual ~ Sample();

	Integer getSize() const;
	Real getX (const Integer) const;
	Real getY (const Integer) const;

	void clear();
	void addToControl  (const Integer);
	void addToLearning (const Integer);
	void setMode (const Mode_ = Sample_ :: DEFAULT);

	void set (const Sample_&);

	template<class S>
	void show (S&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	template<class S>
	void showVector
	(
		S&,
		const RealVector_& xVector,
		const RealVector_& yVector
	) const;

	const RealVector_& xVector_;
	const RealVector_& yVector_;

	Sample_ sample_;
};

}
}


