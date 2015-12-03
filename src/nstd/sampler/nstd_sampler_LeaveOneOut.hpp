/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_sampler_LeaveOneOut.hpp                             */
/* Description:     Leave One Out (LOO) sample generator                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_SAMPLER_LEAVE_ONE_OUT_HPP_
#define NSTD_SAMPLER_LEAVE_ONE_OUT_HPP_

namespace nstd {
namespace sampler {

template<class A>
class LeaveOneOut :
	public Object,
	public memory :: storage :: Scalar<LeaveOneOut<A>, A> {
public :
	typedef A Allocator_;
	typedef Sample<Allocator_> Sample_;

	LeaveOneOut (Sample_& sample);
	virtual ~ LeaveOneOut();

	bool generate();
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
	Sample_& sample_;
	const int size_;
	int count_;
};

}
}

#endif /*NSTD_SAMPLER_LEAVE_ONE_OUT_HPP_*/
