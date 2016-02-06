/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_Static.cpp                                          */
/* Description:     pure static object base class                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	void 
	Static<T> :: init() 
	{
		if (initialized_) {
			return;
		}
		T :: initRaw ();
		initialized_ = true;
	}
	template<class T>
	void 
	Static<T> :: init (const Size_t param) 
	{
		if (initialized_) {
			return;
		}
		T :: initRaw (param);
		initialized_ = true;
	}
	template<class T>
	Size_t 
	Static<T> :: getVolume () 
	{
		if (counted_) {
			return 0;
		} 
		counted_ = true;
		Size_t volume = 0;
		volume += getAggregateVolume (string_);
		volume += T :: getRawVolume();
		return volume;
	}
	template<class T>
	void
	Static<T> :: release()
	{
		if (!initialized_) {
			return;
		}
		T :: releaseRaw ();
		initialized_ = false;
	}

	template<class T>
	template<class A>
	void 
	Static<T> :: show (String<A>& string) 
	{
		if (showed_) {
			return;
		}
		T :: showRaw (string);
		showed_ = true;
	}
	template<class T>
	void 
	Static<T> :: show (std :: ostream& os) 
	{
		if (string_ == NULL) {
			string_ = new String_ (Object :: INITAIL_STRING_CAPACITY);
		} else {
			string_->clear();
		}
		show (*string_);
		os << string_;
	}

	template<class T>
	inline bool 
	Static<T> :: isInitialized() {
		return initialized_;
	}
	template<class T>
	inline bool 
	Static<T> :: isCounted() {
		return initialized_;
	}
	template<class T>
	inline bool 
	Static<T> :: isShowed() {
		return showed_;
	}

	/****************************
	 *		Protected members
	 ****************************/
	
	template<class T>
	template<class S>
	inline Size_t
	Static<T> :: getAggregateVolume (const S* const aggregate)
	{
		Size_t result = 0;
		if (aggregate != NULL) {
			result += aggregate->getVolume();
			result += aggregate->getSizeOf();
		}
		return result;
	}
	template<class T>
	template<class S>
	inline void
	Static<T> :: deleteAggregateObject (S*& aggregate)
	{
		if (aggregate == NULL) {
			return;
		}
		typedef
			typename type :: Unconst<S> :: Result_
			Unconst;
		const_cast<Unconst*>(aggregate)->commitSuicide();
		aggregate = NULL;
	}
	template<class T>
	template<class S>
	inline void
	Static<T> :: deleteAggregateObject (S* const& aggregate)
	{
		if (aggregate == NULL) {
			return;
		}
		typedef
			typename type :: Unconst<S> :: Result_
			Unconst;
		const_cast<Unconst*>(aggregate)->commitSuicide();
		const_cast<T*&>(aggregate) = NULL;
	}

	/***********************************
	 *		Private static atrtributes
	 ***********************************/

	template<class T>
	bool Static<T> :: initialized_ = false;
	template<class T>
	bool Static<T> :: counted_ = false;
	template<class T>
	bool Static<T> :: showed_ = false;

	template<class T>
	typename Static<T> :: String_*
		Static<T> :: string_ = NULL;

}


