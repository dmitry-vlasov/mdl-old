/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_Owl.cpp                                      */
/* Description:     manchester owl translator to del                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_OWL_CPP_
#define DEL_OWL_MAN_OWL_CPP_

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/math/del_math.hpp"
#include "del/owl/man/del_owl_man_Owl.hpp"

namespace del {
namespace owl {
namespace man {

using namespace exception;

	/****************************
	 *		Public members
	 ****************************/

	Owl :: Owl (Del* del) :
	file_ (Config :: getSource().getString()),
	path_ (new Path (file_)),
	parser_ (new parser :: Source()),
	source_ (NULL),
	del_ ((del == NULL) ? Del :: del() : del) {
	}
	Owl :: Owl (const String& file) :
	file_ (file),
	path_ (new Path (file_)),
	parser_ (new parser :: Source()),
	source_ (NULL),
	del_ (NULL) {
	}
	Owl :: ~ Owl()
	{
		deleteAggregateObject (source_);
		deleteAggregateObject (parser_);
		deleteAggregateObject (path_);
		del_ = NULL;
	}

	void
	Owl :: translate()
	{
		if (externalMode()) {
			del_->timers().translate().start();
		}
		read();

		if (Config :: getTarget().isDefined()) {
			write();
		} else {
			output();
		}
		if (externalMode()) {
			del_->timers().translate().stop();
		}
	}
	void
	Owl :: read()
	{
		if (externalMode()) {
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout << "reading ... " << std :: flush;
			}
			del_->timers().read().start();
		}
		source_ = parser_->parse (*path_);
		if (externalMode()) {
			del_->timers().read().stop();
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout << "done in " << del_->timers().read() << std :: endl;
			}
		}
	}
	const source :: Source*
	Owl :: getSource() const {
		return source_;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Owl :: commitSuicide() {
		delete this;
	}
	Size_t
	Owl :: getVolume() const
	{
		Size_t volume = 0;
		volume += file_.getVolume();
		volume += getAggregateVolume (path_);
		volume += getAggregateVolume (parser_);
		volume += getAggregateVolume (source_);
		return volume;
	}
	Size_t
	Owl :: getSizeOf() const {
		return sizeof (Owl);
	}
	void
	Owl :: show (String& string) const
	{
		if (path_ == NULL) {
			string << "file <none>" << space;
		} else {
			string << "file" << space;
			string << *path_ << space;
		}
		string << "is translated in" << space << del_->timers().translate() << endLine;
		string << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Owl :: write()
	{
		if (source_ == NULL) {
			return;
		}
		if (!source_->isWritable()) {
			return;
		}
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "writing ... " << std :: flush;
		}
		source_->write();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done." << std :: endl;
		}
	}
	void
	Owl :: output()
	{
		std :: cout << "<output>" << std :: endl;
		std :: cout << *source_ << std :: endl;
		std :: cout << "</output>" << std :: endl;
	}
	bool
	Owl :: internalMode() const {
		return (del_ == NULL);
	}
	bool
	Owl :: externalMode() const {
		return (del_ != NULL);
	}
}
}
}

#endif /*DEL_OWL_MAN_OWL_CPP_*/
