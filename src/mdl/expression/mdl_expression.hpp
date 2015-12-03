/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression.hpp                                       */
/* Description:     expression module                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_HPP_
#define MDL_EXPRESSION_HPP_

#include "mdl/expression/build/mdl_expression_build.hpp"
#include "mdl/expression/direction/mdl_expression_direction.hpp"
#include "mdl/expression/iterator/mdl_expression_iterator.hpp"
#include "mdl/expression/node/mdl_expression_node.hpp"

#include "mdl/expression/mdl_expression_Array.hpp"
#include "mdl/expression/mdl_expression_Branching.hpp"
#include "mdl/expression/mdl_expression_Bush.hpp"
#include "mdl/expression/mdl_expression_Linear.hpp"
#include "mdl/expression/mdl_expression_Forest.hpp"
#include "mdl/expression/mdl_expression_List.hpp"
#include "mdl/expression/mdl_expression_Mode.hpp"
#include "mdl/expression/mdl_expression_Substitution.hpp"
#include "mdl/expression/mdl_expression_Substiunit.hpp"
#include "mdl/expression/mdl_expression_Symbol.hpp"
#include "mdl/expression/mdl_expression_Term.hpp"
#include "mdl/expression/mdl_expression_Tree.hpp"

#include "mdl/expression/mdl_expression.tpp"

#include "mdl/expression/parse/mdl_expression_parse.hpp"
#include "mdl/expression/unify/mdl_expression_unify.hpp"
#include "mdl/expression/simify/mdl_expression_simify.hpp"

#endif /*MDL_EXPRESSION_HPP_*/
