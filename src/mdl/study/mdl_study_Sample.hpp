/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_Sample.hpp                                     */
/* Description:     sample set for teaching / tuning                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_SAMPLE_HPP_
#define MDL_STUDY_SAMPLE_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {

class Sample :
	public object :: Object,
	public Scalar<Sample> {
public :
	enum Type_ {
		UNIFORM  = 0,
		IN_ORDER = 1,
		DEFAULT  = 0
	};

	Sample (Format&, const Type_ = DEFAULT);
	virtual ~ Sample();

	void build (const value :: Integer size, Time& timeLimit);
	void setSize (const value :: Integer);
	static Time estimateTime (const value :: Integer);

	const Set& getPrimary() const;
	const Set& getSecondary() const;
	const Fitness& getFitness() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void showPrimary (String&, const bool full = false) const;
	void showSecondary (String&, const bool full = false) const;
	void initPrimary();
	void initSecondary();

	Format format_;
	Format subFormat_;
	const Type_ type_;
	value :: Integer size_;

	Set base_;
	Set primary_;
	Set secondary_;

	Experience experience_;
	Fitness    fitness_;
};

}
}

#endif /*MDL_STUDY_SAMPLE_HPP_*/
