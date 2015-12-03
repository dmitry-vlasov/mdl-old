/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_sampler_Sample.cpp                                  */
/* Description:     sample                                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_SAMPLER_SAMPLE_CPP_
#define NSTD_SAMPLER_SAMPLE_CPP_

namespace nstd {
namespace sampler {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Sample<A> :: Sample (const Integer size) :
	mode_ (DEFAULT),
	size_ (size),
	learning_ (NULL),
	control_ (NULL) {
	}
	template<class A>
	Sample<A> :: Sample (const Sample& sample) :
	mode_ (sample.mode_),
	size_ (sample.size_),
	learning_ (new Vector_ (*sample.learning_)),
	control_ (new Vector_ (*sample.control_)) {
	}
	template<class A>
	Sample<A> :: ~ Sample()
	{
		deleteAggregateObject (learning_);
		deleteAggregateObject (control_);
	}

	template<class A>
	typename Sample<A> :: Integer
	Sample<A> :: getSize() const
	{
		switch (mode_) {
		case SAMPLE   : return size_;
		case LEARNING : return learning_->getSize();
		case CONTROL  : return control_->getSize();
		default       : return 0;
		}
	}
	template<class A>
	typename Sample<A> :: Integer
	Sample<A> :: getIndex (const Integer i) const
	{
		switch (mode_) {
		case SAMPLE   : return i;
		case LEARNING : return learning_->getValue (i);
		case CONTROL  : return control_->getValue (i);
		default       : return 0;
		}
	}

	template<class A>
	void
	Sample<A> :: clear()
	{
		if (learning_ == NULL) {
			learning_ = new Vector_ (size_);
			control_ = new Vector_ (size_);
		}
		learning_->clear();
		control_->clear();
	}
	template<class A>
	inline void
	Sample<A> :: setMode (const Mode_ mode) {
		mode_ = mode;
	}

	template<class A>
	inline void
	Sample<A> :: addToControl (const Integer i) {
		control_->add (i);
	}
	template<class A>
	inline void
	Sample<A> :: addToLearning (const Integer i) {
		learning_->add (i);
	}
	template<class A>
	inline bool
	Sample<A> :: isMeaningful (const Integer learningAtLeast) const
	{
		if (learningAtLeast == Undefined<Integer> :: getValue()) {
			return
				(size_ > 0) &&
				(control_->getSize() > 0) &&
				(learning_->getSize() > 0);
		} else {
			return
				(size_ > 0) &&
				(control_->getSize() > 0) &&
				(learning_->getSize() >= learningAtLeast);
		}
	}

	template<class A>
	void
	Sample<A> :: operator = (const Sample& sample)
	{
		if (learning_ == NULL) {
			learning_ = new Vector_ (size_);
			control_ = new Vector_ (size_);
		}
		learning_->copy (*sample.learning_);
		control_->copy (*sample.control_);
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	inline void
	Sample<A> :: showLearning (S& string) const {
		showVector (string, learning_);
	}
	template<class A>
	template<class S>
	inline void
	Sample<A> :: showControl (S& string) const {
		showVector (string, control_);
	}
	template<class A>
	template<class S>
	void
	Sample<A> :: show (S& string) const
	{
		string << "sample size: " << size_ << endLine;
		string << "mode: ";
		switch  (mode_) {
		case SAMPLE   : string << "sample";   break;
		case LEARNING : string << "learning"; break;
		case CONTROL  : string << "control";  break;
		}
		string << endLine;
		string << "learning set: ";
		showVector (string, learning_);
		string << endLine;
		string << "control set: ";
		showVector (string, control_);
		string << endLine;

		string << endLine;
	}

	// object :: Object implementation
	template<class A>
	void
	Sample<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Sample<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (learning_);
		volume += getAggregateVolume (control_);
		return volume;
	}
	template<class A>
	Size_t
	Sample<A> :: getSizeOf() const {
		return sizeof (Sample);
	}
	template<class A>
	void
	Sample<A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	template<class S>
	void
	Sample<A> :: showVector (S& string, const Vector_* vector) const
	{
		string << "{";
		for (Integer i = 0; i < vector->getSize(); ++ i) {
			const Integer index = vector->getValue (i);
			string << index;
			if (i + 1 < vector->getSize()) {
				string << ", ";
			}
		}
		string << "}";
	}
}
}

#endif /*NSTD_SAMPLER_SAMPLE_CPP_*/
