/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_sampler_Sample.hpp                                  */
/* Description:     sample                                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_SAMPLER_SAMPLE_HPP_
#define NSTD_SAMPLER_SAMPLE_HPP_

namespace nstd {
namespace sampler {

template<class A>
class Sample :
	public Object,
	public memory :: storage :: Scalar<Sample<A>, A> {
public :
	typedef A Allocator_;
	typedef int Integer;

	enum Mode_ {
		SAMPLE,
		LEARNING,
		CONTROL,
		DEFAULT = SAMPLE
	};

	Sample (const Integer);
	Sample (const Sample&);
	virtual ~ Sample();

	Integer getSize() const;
	Integer getIndex (const Integer) const;

	void clear();
	void setMode (const Mode_ = DEFAULT);

	void addToControl (const Integer);
	void addToLearning (const Integer);
	bool isMeaningful (const Integer learningAtLeast) const;

	void operator = (const Sample&);

	template<class S>
	void showLearning (S&) const;
	template<class S>
	void showControl (S&) const;
	template<class S>
	void show (S&) const;

	// Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	template<class>
	friend class FoldNx2;
	template<class>
	friend class LeaveOneOut;

	typedef
		container :: Vector
		<
			Integer,
			container :: storage :: ByValue,
			Allocator_
		>
		Vector_;

	template<class S>
	void showVector (S&, const Vector_*) const;

	Mode_ mode_;
	Integer size_;
	Vector_* learning_;
	Vector_* control_;
};

}
}

#endif /*NSTD_SAMPLER_SAMPLE_HPP_*/
