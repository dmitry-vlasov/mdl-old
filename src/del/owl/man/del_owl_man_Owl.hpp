/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_Owl.hpp                                      */
/* Description:     manchester owl translator to del                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_OWL_HPP_
#define DEL_OWL_MAN_OWL_HPP_

#include "del/parser/del_parser.hpp"

namespace del {
namespace owl {
namespace man {

class Owl :
	public Object,
	public Scalar<Owl> {
public :
	Owl (Del*);
	Owl (const String&);
	virtual ~ Owl();

	void translate();
	void read();
	const source :: Source* getSource() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void write();
	void output();
	bool internalMode() const;
	bool externalMode() const;

	const String file_;
	const Path* path_;
	parser :: Source* parser_;
	const source :: Source* source_;
	Del* del_;
};

}
}
}

#endif /*DEL_OWL_MAN_OWL_HPP_*/
