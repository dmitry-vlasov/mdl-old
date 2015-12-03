/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Source.hpp                                      */
/* Description:     source class                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_SOURCE_HPP_
#define MDL_FORM_SOURCE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"

namespace mdl {
namespace form {

class Source :
	public mdl :: interface :: Source,
	public Scalar<Source> {
public :
	typedef
		vector :: object :: Verifiable
		ComponentVector_;

	Source
	(
		bool isTop,
		Lexer*,
		const mdl :: Comments*,
		const Path* sourcePath
	);
	virtual ~ Source();

	static Source* get();
	static void clear();
	static void release();

	// mdl :: Source interface
	virtual void mine() const;

	// mdl :: Components interface
	virtual void addComponentLast (object :: Verifiable* component);
	virtual void addComponentNextTo
	(
		object :: Verifiable* component,
		const object :: Verifiable* sibling
	);
	virtual index :: Assertion getSize() const;
	virtual object :: Verifiable* getComponent (const index :: Assertion);
	virtual const object :: Verifiable* getComponent (const index :: Assertion) const;

	// object :: Verifiable interface
	virtual void check();
	virtual void compress();
	virtual void reprove();
	virtual void prove();
	virtual bool isVerified() const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual void write() const;
	virtual bool lookup() const;
	virtual object :: Writable* find();
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;

private :
	enum {
		INITIAL_COMPONENT_VECTOR_CAPACITY = 32,
		INITIAL_MINE_OUTPUT_CAPACITY = 1024
	};

	void computeTargetPath();

	const bool isTop_;
	Lexer* lexer_;
	Path* sourcePath_;
	Path* targetPath_;
	const mdl :: Comments* comments_;
	ComponentVector_ componentVector_;

	//Output* output_;
	bool isVerified_;

	static Source* source_;
};

}
}

#endif /*MDL_FORM_SOURCE_HPP_*/
