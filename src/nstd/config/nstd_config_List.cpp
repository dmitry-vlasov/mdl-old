/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_List.hpp                                     */
/* Description:     list of config groups                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_LIST_CPP_
#define NSTD_CONFIG_LIST_CPP_

namespace nstd {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	List :: List() :
	groupVector_ (NULL),
	hasAllGroup_ (true) {
	}
	List :: List (const char* groups[], const int count) :
	groupVector_ (count > 0 ? new GroupVector_(count) : NULL),
	hasAllGroup_ (false) {
		for (int i = 0; i < count; ++ i) {
			const char* group = groups[i];
			groupVector_->add (group);
			if (Base :: equalStrings(group, "all")) {
				hasAllGroup_ = true;
			}
		}
	}
	List :: List (const List& list) :
	groupVector_ (new GroupVector_(*list.groupVector_)),
	hasAllGroup_ (list.hasAllGroup_) {
	}
	List :: ~ List()
	{
		if (groupVector_ != NULL) {
			groupVector_->commitSuicide();
			groupVector_ = NULL;
		}
	}

	bool
	List :: contains (const char* group_1) const {
		if (hasAllGroup_) {
			return true;
		}
		if (groupVector_ == NULL) {
			return false;
		}
		for (int i = 0; i < groupVector_->getSize(); ++ i) {
			const char* group_2 = groupVector_->getValue(i);
			if (Base :: equalStrings (group_1, group_2)) {
				return true;
			}
		}
		return false;
	}

	void
	List :: commitSuicide() {
		delete this;
	}
	Size_t
	List :: getVolume() const {
		Size_t volume = 0;
		if (groupVector_ != NULL) {
			volume += groupVector_->getVolume();
			volume += groupVector_->getSizeOf();
		}
		return volume;
	}
	Size_t
	List :: getSizeOf() const {
		return sizeof(List);
	}
	template<class S>
	void
	List :: show (S& s) const
	{
		if (hasAllGroup_) {
			s << "<all>";
			return;
		}
		if (groupVector_ == NULL) {
			s << "<empty>";
			return;
		}
		for (int i = 0; i < groupVector_->getSize(); ++ i) {
			const char* group = groupVector_->getValue(i);
			if (i == 0) {
				s << group;
			} else {
				s << ", " << group;
			}
		}
	}
}
}

#endif /*NSTD_CONFIG_LIST_CPP_*/
