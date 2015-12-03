$(
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
                           Pre-logic
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
$)

  $( Declare the primitive constant symbols for propositional calculus. $)
  $c ( $.  $( Left parenthesis $)
  $c ) $.  $( Right parenthesis $)
  $c -> $. $( Right arrow (read:  "implies") $)
  $c -. $. $( Right handle (read:  "not") $)
  $c wff $. $( Well-formed formula symbol (read:  "the following symbol
               sequence is a wff") $)
  $c |- $. $( Turnstile (read:  "the following symbol sequence is provable" or
              'a proof exists for") $)

  $( Introduce some variable names we will use to represent well-formed
     formulas (wff's). $)
  $v ph $. $( Greek phi $)
  $v ps $.  $( Greek psi $)
  $v ch $.  $( Greek chi $)
  $v th $.  $( Greek theta $)
  $v ta $.  $( Greek tau $)

  $( Specify some variables that we will use to represent wff's.
     The fact that a variable represents a wff is relevant only to a theorem
     referring to that variable, so we may use $f hypotheses.  The symbol
     ` wff ` specifies that the variable that follows it represents a wff. $)
  $( Let variable ` ph ` be a wff. $)
  wph $f wff ph $.
  $( Let variable ` ps ` be a wff. $)
  wps $f wff ps $.
  $( Let variable ` ch ` be a wff. $)
  wch $f wff ch $.
  $( Let variable ` th ` be a wff. $)
  wth $f wff th $.
  $( Let variable ` ta ` be a wff. $)
  wta $f wff ta $.

$(
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
                           Propositional calculus
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
$)

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Recursively define primitive wffs for propositional calculus
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

  $( If ` ph ` is a wff, so is ` -. ph ` or "not ` ph ` ."  Part of the
     recursive definition of a wff (well-formed formula).  In classical logic
     (which is our logic), a wff is interpreted as either true or false.
     So if ` ph ` is true, then ` -. ph ` is false; if ` ph ` is false, then
     ` -. ph ` is true.  Traditionally, Greek letters are used to represent
     wffs, and we follow this convention.  In propositional calculus, we define
     only wffs built up from other wffs, i.e. there is no starting or "atomic"
     wff.  Later, in predicate calculus, we will extend the basic wff
     definition by including atomic wffs ( ~ weq and ~ wel ). $)
  wn $a wff -. ph $.

  $( If ` ph ` and ` ps ` are wff's, so is ` ( ph -> ps ) ` or " ` ph ` implies
     ` ps ` ."  Part of the recursive definition of a wff.  The resulting wff
     is (interpreted as) false when ` ph ` is true and ` ps ` is false; it is
     true otherwise.  (Think of the truth table for an OR gate with input
     ` ph ` connected through an inverter.)  The left-hand wff is called the
     antecedent, and the right-hand wff is called the consequent.  In the case
     of ` ( ph -> ( ps -> ch ) ) ` , the middle ` ps ` may be informally called
     either an antecedent or part of the consequent depending on context. $)
  wi $a wff ( ph -> ps ) $.

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        The axioms of propositional calculus
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

  $(
     Postulate the three axioms of classical propositional calculus.
  $)

  $( Axiom _Simp_.  Axiom A1 of [Margaris] p. 49.  One of the 3 axioms of
     propositional calculus.  The 3 axioms are also given as Definition 2.1
     of [Hamilton] p. 28.  This axiom is called _Simp_ or "the principle of
     simplification" in _Principia Mathematica_ (Theorem *2.02 of
     [WhiteheadRussell] p. 100) because "it enables us to pass from the joint
     assertion of ` ph ` and ` ps ` to the assertion of ` ph ` simply."

     _General remarks_:  Propositional calculus (axioms ~ ax-1 through ~ ax-3
     and rule ~ ax-mp ) can be thought of as asserting formulas that are
     universally "true" when their variables are replaced by any combination
     of "true" and "false."  Propositional calculus was first formalized by
     Frege in 1879, using as his axioms (in addition to rule ~ ax-mp ) the
     wffs ~ ax-1 , ~ ax-2 , ~ pm2.04 , ~ con3 , ~ nega , and ~ negb .  Around
     1930, Lukasiewicz simplified the system by eliminating the third (which
     follows from the first two, as you can see by looking at the proof of
     ~ pm2.04 ) and replacing the last three with our ~ ax-3 .  (Thanks to Ted
     Ulrich for this information.)

     The theorems of propositional calculus are also called _tautologies_.
     Tautologies can be proved very simply using truth tables, based on the
     true/false interpretation of propositional calculus.  To do this, we
     assign all possible combinations of true and false to the wff variables
     and verify that the result (using the rules described in ~ wi and ~ wn )
     always evaluates to true.  This is called the _semantic_ approach.  Our
     approach is called the _syntactic_ approach, in which everything is
     derived from axioms.  A metatheorem called the Completeness Theorem for
     Propositional Calculus shows that the two approaches are equivalent and
     even provides an algorithm for automatically generating syntactic proofs
     from a truth table.  Those proofs, however, tend to be long, and the
     much shorter proofs that we show here were found manually.  Truth tables
     grow exponentially with the number of variables, but it is unknown if the
     same is true of proofs - an answer to this would resolve the P=NP
     conjecture in complexity theory. $)
  ax-1 $a |- ( ph -> ( ps -> ph ) ) $.
  $( [ ?] $) $( [ ?] $)

  $( Axiom _Frege_.  Axiom A2 of [Margaris] p. 49.  One of the 3 axioms of
     propositional calculus.  It "distributes" an antecedent over two
     consequents.  This axiom was part of Frege's original system and is known
     as _Frege_ in the literature.  It is also proved as Theorem *2.77 of
     [WhiteheadRussell] p. 108.  The other direction of this axiom also
     turns out to be true, as demonstrated by ~ pm5.41 . $)
  ax-2 $a |- ( ( ph -> ( ps -> ch ) ) -> ( ( ph -> ps ) -> ( ph -> ch ) ) ) $.

  $( Axiom _Transp_.  Axiom A3 of [Margaris] p. 49.  One of the 3 axioms of
     propositional calculus.  It swaps or "transposes" the order of the
     consequents when negation is removed.  An informal example is that the
     statement "if there are no clouds in the sky, it is not raining" implies
     the statement "if it is raining, there are clouds in the sky."  This
     axiom is called _Transp_ or "the principle of transposition" in
     _Principia Mathematica_ (Theorem *2.17 of [WhiteheadRussell] p. 103).
     We will also use the term "contraposition" for this principle, although
     the reader is advised that in the field of philosophical logic,
     "contraposition" has a different technical meaning. $)
  ax-3 $a |- ( ( -. ph -> -. ps ) -> ( ps -> ph ) ) $.

  $(
     Postulate the modus ponens rule of inference.
  $)

  ${
    $( Minor premise for modus ponens. $)
    min $e |- ph $.
    $( Major premise for modus ponens. $)
    maj $e |- ( ph -> ps ) $.
    $( Rule of Modus Ponens.  The postulated inference rule of propositional
       calculus.  See e.g. Rule 1 of [Hamilton] p. 73.  The rule says, "if
       ` ph ` is true, and ` ph ` implies ` ps ` , then ` ps ` must also be
       true."  This rule is sometimes called "detachment," since it detaches
       the minor premise from the major premise. $)
    ax-mp $a |- ps $.
  $}

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Logical implication
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

$( The results in this section make use of the first 2 axioms only.  In
   an implication, the wff before the arrow is called the "antecedent"
   and the wff after the arrow is called the "consequent." $)

$( We will use the following descriptive terms very loosely:  A "theorem"
   usually has no $e hypotheses.  An "inference" has one or more $e hypotheses.
   A "deduction" is an inference in which the hypotheses and the result
   share the same antecedent. $)

  ${
    $( Premise for ~ a1i . $)
    a1i.1 $e |- ph $.
    $( Inference derived from axiom ~ ax-1 .  See ~ a1d for an explanation of
       our informal use of the terms "inference" and "deduction." $)
    a1i $p |- ( ps -> ph ) $=
      wph wps wph wi a1i.1 wph wps ax-1 ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    $( Premise for ~ a2i . $)
    a2i.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Inference derived from axiom ~ ax-2 . $)
    a2i $p |- ( ( ph -> ps ) -> ( ph -> ch ) ) $=
      wph wps wch wi wi wph wps wi wph wch wi wi a2i.1 wph wps wch ax-2 ax-mp
      $.
      $( [5-Aug-1993] $)
  $}

  ${
    $( First of 2 premises for ~ syl . $)
    syl.1 $e |- ( ph -> ps ) $.
    $( Second of 2 premises for ~ syl . $)
    syl.2 $e |- ( ps -> ch ) $.
    $( An inference version of the transitive laws for implication ~ imim2 and
       ~ imim1 , which Russell and Whitehead call "the principle of the
       syllogism...because...the syllogism in Barbara is derived from them"
       (quote after Theorem *2.06 of [WhiteheadRussell] p. 101).  Some authors
       call this law a "hypothetical syllogism."

       (A bit of trivia:  this is the most commonly referenced assertion in our
       database.  In second place is ~ ax-mp , followed by ~ visset , ~ bitr ,
       ~ imp , and ~ ex .  The Metamath program command 'show usage' shows the
       number of references.) $)
    syl $p |- ( ph -> ch ) $=
      wph wps wi wph wch wi syl.1 wph wps wch wps wch wi wph syl.2 a1i a2i
      ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    $( Premise for ~ com12 .  See ~ pm2.04 for the theorem form. $)
    com12.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Inference that swaps (commutes) antecedents in an implication. $)
    com12 $p |- ( ps -> ( ph -> ch ) ) $=
      wps wph wps wi wph wch wi wps wph ax-1 wph wps wch com12.1 a2i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    a1d.1 $e |- ( ph -> ps ) $.
    $( Deduction introducing an embedded antecedent.  (The proof was revised by
       Stefan Allan, 20-Mar-06.)

       _Naming convention_:  We often call a theorem a "deduction" and suffix
       its label with "d" whenever the hypotheses and conclusion are each
       prefixed with the same antecedent.  This allows us to use the theorem in
       places where (in traditional textbook formalizations) the standard
       Deduction Theorem would be used; here ` ph ` would be replaced with a
       conjunction ( ~ df-an ) of the hypotheses of the would-be deduction.  By
       contrast, we tend to call the simpler version with no common antecedent
       an "inference" and suffix its label with "i"; compare theorem ~ a1i .
       Finally, a "theorem" would be the form with no hypotheses; in this case
       the "theorem" form would be the original axiom ~ ax-1 .  In
       propositional calculus we usually prove the theorem form first without a
       suffix on its label (e.g.  ~ pm2.43 vs.  ~ pm2.43i vs.  ~ pm2.43d ), but
       (much) later we often suffix the theorem form's label with "t" as in
       ~ negnegt vs. ~ negneg , especially when our "weak deduction theorem"
       ~ dedth is used to prove the theorem form from its inference form.  When
       an inference is converted to a theorem by eliminating an "is a set"
       hypothesis, we sometimes suffix the theorem form with "g" (for somewhat
       overstated "generalized") as in ~ uniex vs.  ~ uniexg . $)
    a1d $p |- ( ph -> ( ch -> ps ) ) $=
      wph wps wch wps wi a1d.1 wps wch ax-1 syl $.
      $( [20-Mar-2006] $) $( [5-Aug-1993] $)
  $}

  ${
    a2d.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( Deduction distributing an embedded antecedent. $)
    a2d $p |- ( ph -> ( ( ps -> ch ) -> ( ps -> th ) ) ) $=
      wph wps wch wth wi wi wps wch wi wps wth wi wi a2d.1 wps wch wth ax-2 syl
      $.
      $( [23-Jun-1994] $)
  $}

  $( A closed form of syllogism (see ~ syl ).  Theorem *2.05 of
     [WhiteheadRussell] p. 100. $)
  imim2 $p |- ( ( ph -> ps ) -> ( ( ch -> ph ) -> ( ch -> ps ) ) ) $=
    wph wps wi wch wph wps wph wps wi wch ax-1 a2d $.
    $( [5-Aug-1993] $)

  $( A closed form of syllogism (see ~ syl ).  Theorem *2.06 of
     [WhiteheadRussell] p. 100. $)
  imim1 $p |- ( ( ph -> ps ) -> ( ( ps -> ch ) -> ( ph -> ch ) ) ) $=
    wps wch wi wph wps wi wph wch wi wps wch wph imim2 com12 $.
    $( [5-Aug-1993] $)

  ${
    imim1i.1 $e |- ( ph -> ps ) $.
    $( Inference adding common consequents in an implication, thereby
       interchanging the original antecedent and consequent. $)
    imim1i $p |- ( ( ps -> ch ) -> ( ph -> ch ) ) $=
      wph wps wi wps wch wi wph wch wi wi imim1i.1 wph wps wch imim1 ax-mp $.
      $( [5-Aug-1993] $)

    $( Inference adding common antecedents in an implication. $)
    imim2i $p |- ( ( ch -> ph ) -> ( ch -> ps ) ) $=
      wch wph wps wph wps wi wch imim1i.1 a1i a2i $.
      $( [5-Aug-1993] $)
  $}

  ${
    imim12i.1 $e |- ( ph -> ps ) $.
    imim12i.2 $e |- ( ch -> th ) $.
    $( Inference joining two implications. $)
    imim12i $p |- ( ( ps -> ch ) -> ( ph -> th ) ) $=
      wps wch wi wps wth wi wph wth wi wch wth wps imim12i.2 imim2i wph wps wth
      imim12i.1 imim1i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    imim3i.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Inference adding three nested antecedents. $)
    imim3i $p |- ( ( th -> ph ) -> ( ( th -> ps ) -> ( th -> ch ) ) ) $=
      wth wph wi wth wps wch wph wps wch wi wth imim3i.1 imim2i a2d $.
      $( [19-Dec-2006] $) $( [19-Dec-2006] $)
  $}

  ${
    3syl.1 $e |- ( ph -> ps ) $.
    3syl.2 $e |- ( ps -> ch ) $.
    3syl.3 $e |- ( ch -> th ) $.
    $( Inference chaining two syllogisms. $)
    3syl $p |- ( ph -> th ) $=
      wph wch wth wph wps wch 3syl.1 3syl.2 syl 3syl.3 syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl5.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl5.2 $e |- ( th -> ps ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the second antecedent of the first premise. $)
    syl5 $p |- ( ph -> ( th -> ch ) ) $=
      wph wps wch wi wth wch wi syl5.1 wth wps wch syl5.2 imim1i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl6.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl6.2 $e |- ( ch -> th ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the consequent of the first premise. $)
    syl6 $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wps wth wi syl6.1 wch wth wps syl6.2 imim2i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl7.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl7.2 $e |- ( ta -> ch ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the third antecedent of the first premise. $)
    syl7 $p |- ( ph -> ( ps -> ( ta -> th ) ) ) $=
      wph wps wch wth wi wta wth wi syl7.1 wta wch wth syl7.2 imim1i syl6 $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl8.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl8.2 $e |- ( th -> ta ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the consequent of the first premise. $)
    syl8 $p |- ( ph -> ( ps -> ( ch -> ta ) ) ) $=
      wph wps wch wth wi wch wta wi syl8.1 wth wta wch syl8.2 imim2i syl6 $.
      $( [1-Aug-1994] $)
  $}

  ${
    imim2d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction adding nested antecedents. $)
    imim2d $p |- ( ph -> ( ( th -> ps ) -> ( th -> ch ) ) ) $=
      wph wth wps wch wph wps wch wi wth imim2d.1 a1d a2d $.
      $( [5-Aug-1993] $)
  $}

  ${
    mpd.1 $e |- ( ph -> ps ) $.
    mpd.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( A modus ponens deduction. $)
    mpd $p |- ( ph -> ch ) $=
      wph wps wi wph wch wi mpd.1 wph wps wch mpd.2 a2i ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    syld.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syld.2 $e |- ( ph -> ( ch -> th ) ) $.
    $( Syllogism deduction.  (The proof was shortened by Mel L. O'Cat,
       19-Feb-2008.  See ~ syldOLD for previous version.) $)
    syld $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wps wth wi syld.1 wph wch wth wps syld.2 imim2d mpd $.
      $( [19-Feb-2008] $) $( [5-Aug-1993] $)

    $( Syllogism deduction.  (The proof was shortened by Mel L. O'Cat,
       7-Aug-2004.) $)
    syldOLD $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wi wph wps wth wi wi syld.1 wph wps wch wi wps wth wi wph
      wch wth wps syld.2 imim2d a2i ax-mp $.
      $( [7-Aug-2004] $) $( [5-Aug-1993] $)
  $}

  ${
    imim1d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction adding nested consequents. $)
    imim1d $p |- ( ph -> ( ( ch -> th ) -> ( ps -> th ) ) ) $=
      wph wps wch wi wch wth wi wps wth wi wi imim1d.1 wps wch wth imim1 syl $.
      $( [3-Apr-1994] $)
  $}

  ${
    imim12d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    imim12d.2 $e |- ( ph -> ( th -> ta ) ) $.
    $( Deduction combining antecedents and consequents. $)
    imim12d $p |- ( ph -> ( ( ch -> th ) -> ( ps -> ta ) ) ) $=
      wph wch wth wi wps wth wi wps wta wi wph wps wch wth imim12d.1 imim1d wph
      wth wta wps imim12d.2 imim2d syld $.
      $( [7-Aug-1994] $)
  $}

  $( Swap antecedents.  Theorem *2.04 of [WhiteheadRussell] p. 100. $)
  pm2.04 $p |- ( ( ph -> ( ps -> ch ) ) -> ( ps -> ( ph -> ch ) ) ) $=
    wph wps wch wi wi wph wps wi wph wch wi wps wph wps wch ax-2 wps wph ax-1
    syl5 $.
    $( [5-Aug-1993] $)

  $( Theorem *2.83 of [WhiteheadRussell] p. 108. $)
  pm2.83 $p |-  ( ( ph -> ( ps -> ch ) ) -> ( ( ph -> ( ch -> th ) ) ->
                ( ph -> ( ps -> th ) ) ) ) $=
    wps wch wi wch wth wi wps wth wi wph wps wch wth imim1 imim3i $.
    $( [13-Jan-2005] $) $( [3-Jan-2005] $)

  ${
    com3.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( Commutation of antecedents.  Swap 2nd and 3rd. $)
    com23 $p |- ( ph -> ( ch -> ( ps -> th ) ) ) $=
      wph wps wch wth wi wi wch wps wth wi wi com3.1 wps wch wth pm2.04 syl $.
      $( [5-Aug-1993] $)

    $( Commutation of antecedents.  Swap 1st and 3rd. $)
    com13 $p |- ( ch -> ( ps -> ( ph -> th ) ) ) $=
      wps wch wph wth wi wps wph wch wth wph wps wch wth wi com3.1 com12 com23
      com12 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate left. $)
    com3l $p |- ( ps -> ( ch -> ( ph -> th ) ) ) $=
      wph wch wps wth wph wps wch wth com3.1 com23 com13 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate right. $)
    com3r $p |- ( ch -> ( ph -> ( ps -> th ) ) ) $=
      wps wch wph wth wph wps wch wth com3.1 com3l com3l $.
      $( [25-Apr-1994] $)
  $}

  ${
    com4.1 $e |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $.
    $( Commutation of antecedents.  Swap 3rd and 4th. $)
    com34 $p |- ( ph -> ( ps -> ( th -> ( ch -> ta ) ) ) ) $=
      wph wps wch wth wta wi wi wth wch wta wi wi com4.1 wch wth wta pm2.04
      syl6 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Swap 2nd and 4th. $)
    com24 $p |- ( ph -> ( th -> ( ch -> ( ps -> ta ) ) ) ) $=
      wph wth wps wch wta wph wps wth wch wta wi wph wps wch wth wta com4.1
      com34 com23 com34 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Swap 1st and 4th. $)
    com14 $p |- ( th -> ( ps -> ( ch -> ( ph -> ta ) ) ) ) $=
      wth wps wph wch wta wph wps wth wch wta wi wph wps wch wth wta com4.1
      com34 com13 com34 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate left.  (The proof was shortened by
       Mel L. O'Cat, 15-Aug-2004.) $)
    com4l $p |- ( ps -> ( ch -> ( th -> ( ph -> ta ) ) ) ) $=
      wth wps wch wph wta wi wph wps wch wth wta com4.1 com14 com3l $.
      $( [15-Aug-2004] $) $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate twice. $)
    com4t $p |- ( ch -> ( th -> ( ph -> ( ps -> ta ) ) ) ) $=
      wps wch wth wph wta wph wps wch wth wta com4.1 com4l com4l $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate right. $)
    com4r $p |- ( th -> ( ph -> ( ps -> ( ch -> ta ) ) ) ) $=
      wch wth wph wps wta wph wps wch wth wta com4.1 com4t com4l $.
      $( [25-Apr-1994] $)
  $}

  ${
    a1dd.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction introducing a nested embedded antecedent.  (The proof was
       shortened by Mel L. O'Cat, 15-Jan-2008.) $)
    a1dd $p |- ( ph -> ( ps -> ( th -> ch ) ) ) $=
      wph wps wch wth wch wi a1dd.1 wch wth ax-1 syl6 $.
      $( [15-Jan-2008] $) $( [17-Dec-2004] $)
  $}

  ${
    mp2.1 $e |- ph $.
    mp2.2 $e |- ps $.
    mp2.3 $e |- ( ph -> ( ps -> ch ) ) $.
    $( A double modus ponens inference. $)
    mp2 $p |- ch $=
      wps wch mp2.2 wph wps wch wi mp2.1 mp2.3 ax-mp ax-mp $.
      $( [5-Apr-1994] $)
  $}

  ${
    mpi.1 $e |- ps $.
    mpi.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( A nested modus ponens inference.  (The proof was shortened by Stefan
       Allan, 20-Mar-06. $)
    mpi $p |- ( ph -> ch ) $=
      wph wps wch wps wph mpi.1 a1i mpi.2 mpd $.
      $( [20-Mar-2006] $) $( [5-Aug-1993] $)
  $}

  ${
    mpii.1 $e |- ch $.
    mpii.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A doubly nested modus ponens inference. $)
    mpii $p |- ( ph -> ( ps -> th ) ) $=
      wph wch wps wth wi mpii.1 wph wps wch wth mpii.2 com23 mpi $.
      $( [31-Dec-1993] $)
  $}

  ${
    mpdd.1 $e |- ( ph -> ( ps -> ch ) ) $.
    mpdd.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A nested modus ponens deduction. $)
    mpdd $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wps wth wi mpdd.1 wph wps wch wth mpdd.2 a2d mpd $.
      $( [13-Dec-2004] $) $( [12-Dec-2004] $)
  $}

  ${
    mpid.1 $e |- ( ph -> ch ) $.
    mpid.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A nested modus ponens deduction. $)
    mpid $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth wph wch wps mpid.1 a1d mpid.2 mpdd $.
      $( [16-Dec-2004] $) $( [14-Dec-2004] $)
  $}

  ${
    mpdi.1 $e |- ( ps -> ch ) $.
    mpdi.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A nested modus ponens deduction.  (The proof was shortened by Mel L.
       O'Cat, 15-Jan-2008.) $)
    mpdi $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth wps wch wi wph mpdi.1 a1i mpdi.2 mpdd $.
      $( [15-Jan-2008] $) $( [16-Apr-2005] $)
  $}

  ${
    mpcom.1 $e |- ( ps -> ph ) $.
    mpcom.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Modus ponens inference with commutation of antecedents. $)
    mpcom $p |- ( ps -> ch ) $=
      wps wph wch mpcom.1 wph wps wch mpcom.2 com12 mpd $.
      $( [17-Mar-1996] $)
  $}

  ${
    syldd.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syldd.2 $e |- ( ph -> ( ps -> ( th -> ta ) ) ) $.
    $( Nested syllogism deduction. $)
    syldd $p |- ( ph -> ( ps -> ( ch -> ta ) ) ) $=
      wph wps wch wth wi wch wta wi syldd.1 wph wps wth wta wi wch wth wi wch
      wta wi wi syldd.2 wth wta wch imim2 syl6 mpdd $.
      $( [13-Dec-2004] $) $( [12-Dec-2004] $)
  $}

  ${
    sylcom.1 $e |- ( ph -> ( ps -> ch ) ) $.
    sylcom.2 $e |- ( ps -> ( ch -> th ) ) $.
    $( Syllogism inference with commutation of antecedents.  (The proof was
       shortened by Mel O'Cat, 2-Feb-06 and shortened further by Stefan Allan,
       23-Feb-06.) $)
    sylcom $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wps wth wi sylcom.1 wps wch wth sylcom.2 a2i syl $.
      $( [24-Feb-2006] $) $( [29-Aug-2004] $)
  $}

  ${
    syl5com.2 $e |- ( ph -> ( ps -> ch ) ) $.
    syl5com.1 $e |- ( th -> ps ) $.
    $( Syllogism inference with commuted antecedents. $)
    syl5com $p |- ( th -> ( ph -> ch ) ) $=
      wth wph wps wch wth wps wph syl5com.1 a1d syl5com.2 sylcom $.
      $( [25-May-2005] $) $( [24-May-2005] $)
  $}

  ${
    syl6com.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl6com.2 $e |- ( ch -> th ) $.
    $( Syllogism inference with commuted antecedents. $)
    syl6com $p |- ( ps -> ( ph -> th ) ) $=
      wph wps wth wph wps wch wth syl6com.1 syl6com.2 syl6 com12 $.
      $( [26-May-2005] $) $( [25-May-2005] $)
  $}

  ${
    syli.1 $e |- ( ps -> ( ph -> ch ) ) $.
    syli.2 $e |- ( ch -> ( ph -> th ) ) $.
    $( Syllogism inference with common nested antecedent. $)
    syli $p |- ( ps -> ( ph -> th ) ) $=
      wps wph wch wth syli.1 wch wph wth syli.2 com12 sylcom $.
      $( [5-Nov-2004] $) $( [4-Nov-2004] $)
  $}

  ${
    syl5d.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl5d.2 $e |- ( ph -> ( ta -> ch ) ) $.
    $( A nested syllogism deduction.  (The proof was shortened by Josh
       Purinton, 29-Dec-00 and shortened further by Mel O'Cat, 2-Feb-06.) $)
    syl5d $p |- ( ph -> ( ps -> ( ta -> th ) ) ) $=
      wph wps wta wch wth wph wta wch wi wps syl5d.2 a1d syl5d.1 syldd $.
      $( [3-Feb-2006] $) $( [5-Aug-1993] $)
  $}

  ${
    syl6d.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl6d.2 $e |- ( ph -> ( th -> ta ) ) $.
    $( A nested syllogism deduction.  (The proof was shortened by Josh
       Purinton, 29-Dec-00 and shortened further by Mel O'Cat, 2-Feb-06.) $)
    syl6d $p |- ( ph -> ( ps -> ( ch -> ta ) ) ) $=
      wph wps wch wth wta syl6d.1 wph wth wta wi wps syl6d.2 a1d syldd $.
      $( [3-Feb-2006] $) $( [5-Aug-1993] $)
  $}

  ${
    syl9.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl9.2 $e |- ( th -> ( ch -> ta ) ) $.
    $( A nested syllogism inference with different antecedents.  (The proof
       was shortened by Josh Purinton, 29-Dec-00.) $)
    syl9 $p |- ( ph -> ( th -> ( ps -> ta ) ) ) $=
      wph wth wch wta wps wth wch wta wi wi wph syl9.2 a1i syl9.1 syl5d $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl9r.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl9r.2 $e |- ( th -> ( ch -> ta ) ) $.
    $( A nested syllogism inference with different antecedents. $)
    syl9r $p |- ( th -> ( ph -> ( ps -> ta ) ) ) $=
      wph wth wps wta wi wph wps wch wth wta syl9r.1 syl9r.2 syl9 com12 $.
      $( [5-Aug-1993] $)
  $}

  $( Principle of identity.  Theorem *2.08 of [WhiteheadRussell] p. 101.
     For another version of the proof directly from axioms, see ~ id1 .
     (The proof was shortened by Stefan Allan, 20-Mar-06.) $)
  id $p |- ( ph -> ph ) $=
    wph wph wph wi wph wph wph ax-1 wph wph wph wi ax-1 mpd $.
    $( [20-Mar-2006] $) $( [20-Mar-2006] $)

  $( Principle of identity.  Theorem *2.08 of [WhiteheadRussell] p. 101.  This
     version is proved directly from the axioms for demonstration purposes.
     This proof is a very popular example in the literature and is identical,
     step for step, to the proofs of Theorem 1 of [Margaris] p. 51,
     Example 2.7(a) of [Hamilton] p. 31, Lemma 10.3 of [BellMachover] p. 36,
     and Lemma 1.8 of [Mendelson] p. 36.  It is also
     "Our first proof" in Hirst and Hirst's _A Primer for Logic and Proof_
     p. 16 (PDF p. 22) at
     ~ http://www.mathsci.appstate.edu/~~jlh/primer/hirst.pdf .
     For a shorter version of the proof that takes advantage of previously
     proved theorems, see ~ id . $)
  id1 $p |- ( ph -> ph ) $=
    wph wph wph wi wi wph wph wi wph wph ax-1 wph wph wph wi wph wi wi wph wph
    wph wi wi wph wph wi wi wph wph wph wi ax-1 wph wph wph wi wph ax-2 ax-mp
    ax-mp $.
    $( [5-Aug-1993] $)

  $( Principle of identity with antecedent. $)
  idd $p |- ( ph -> ( ps -> ps ) ) $=
    wps wps wi wph wps id a1i $.
    $( [26-Nov-1995] $)

  $( This theorem, called "Assertion," can be thought of as closed form of
     modus ponens.  Theorem *2.27 of [WhiteheadRussell] p. 104. $)
  pm2.27 $p |- ( ph -> ( ( ph -> ps ) -> ps ) ) $=
    wph wps wi wph wps wph wps wi id com12 $.
    $( [5-Aug-1993] $)

  $( Absorption of redundant antecedent.  Also called the "Contraction" or
     "Hilbert" axiom.  Theorem *2.43 of [WhiteheadRussell] p. 106.  (The proof
     was shortened by Mel L. O'Cat, 15-Aug-2004.) $)
  pm2.43 $p |- ( ( ph -> ( ph -> ps ) ) -> ( ph -> ps ) ) $=
    wph wph wps wi wps wph wps pm2.27 a2i $.
    $( [15-Aug-2004] $) $( [5-Aug-1993] $)

  ${
    pm2.43i.1 $e |- ( ph -> ( ph -> ps ) ) $.
    $( Inference absorbing redundant antecedent. $)
    pm2.43i $p |- ( ph -> ps ) $=
      wph wph wps wi wi wph wps wi pm2.43i.1 wph wps pm2.43 ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    pm2.43d.1 $e |- ( ph -> ( ps -> ( ps -> ch ) ) ) $.
    $( Deduction absorbing redundant antecedent.  (The proof was shortened by
       Mel O'Cat, 3-Feb-06.) $)
    pm2.43d $p |- ( ph -> ( ps -> ch ) ) $=
      wph wps wps wch wph wps idd pm2.43d.1 mpdd $.
      $( [4-Feb-2006] $) $( [18-Aug-1993] $)
  $}

  ${
    pm2.43a.1 $e |- ( ps -> ( ph -> ( ps -> ch ) ) ) $.
    $( Inference absorbing redundant antecedent.  (The proof was shortened by
       Mel O'Cat, 3-Feb-06.) $)
    pm2.43a $p |- ( ps -> ( ph -> ch ) ) $=
      wps wph wps wch wps wph ax-1 pm2.43a.1 mpdd $.
      $( [4-Feb-2006] $) $( [7-Nov-1995] $)

    $( Inference absorbing redundant antecedent. $)
    pm2.43b $p |- ( ph -> ( ps -> ch ) ) $=
      wps wph wch wph wps wch pm2.43a.1 pm2.43a com12 $.
      $( [31-Oct-1995] $)
  $}

  ${
    sylc.1 $e |- ( ph -> ( ps -> ch ) ) $.
    sylc.2 $e |- ( th -> ph ) $.
    sylc.3 $e |- ( th -> ps ) $.
    $( A syllogism inference combined with contraction. $)
    sylc $p |- ( th -> ch ) $=
      wth wps wch sylc.3 wth wph wps wch wi sylc.2 sylc.1 syl mpd $.
      $( [4-May-1994] $)
  $}

  $( Converse of axiom ~ ax-2 .  Theorem *2.86 of [WhiteheadRussell] p. 108. $)
  pm2.86 $p |- ( ( ( ph -> ps ) -> ( ph -> ch ) ) ->
               ( ph -> ( ps -> ch ) ) ) $=
    wph wps wi wph wch wi wi wps wph wch wps wph wps wi wph wch wi wps wph ax-1
    imim1i com23 $.
    $( [25-Apr-1994] $)

  ${
    pm2.86i.1 $e |- ( ( ph -> ps ) -> ( ph -> ch ) ) $.
    $( Inference based on ~ pm2.86 . $)
    pm2.86i $p |- ( ph -> ( ps -> ch ) ) $=
      wph wps wi wph wch wi wi wph wps wch wi wi pm2.86i.1 wph wps wch pm2.86
      ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    pm2.86d.1 $e |- ( ph -> ( ( ps -> ch ) -> ( ps -> th ) ) ) $.
    $( Deduction based on ~ pm2.86 . $)
    pm2.86d $p |- ( ph -> ( ps -> ( ch -> th ) ) ) $=
      wph wps wch wi wps wth wi wi wps wch wth wi wi pm2.86d.1 wps wch wth
      pm2.86 syl $.
      $( [29-Jun-1995] $)
  $}

  $( The Linearity Axiom of the infinite-valued sentential logic (L-infinity)
     of Lukasiewicz.  (Contributed by Mel L. O'Cat, 12-Aug-2004.) $)
  loolin $p |- ( ( ( ph -> ps ) -> ( ps -> ph ) ) -> ( ps -> ph ) ) $=
    wph wps wi wps wph wi wi wps wph wps wph wps wi wps wph wi wps wph ax-1
    imim1i pm2.43d $.
    $( [14-Aug-2004] $) $( [12-Aug-2004] $)

  $( An alternate for the Linearity Axiom of the infinite-valued sentential
     logic (L-infinity) of Lukasiewicz, due to Barbara Wozniakowska, _Reports
     on Mathematical Logic_ 10, 129-137 (1978).  (Contributed by Mel L. O'Cat,
     8-Aug-2004.) $)
  loowoz $p |- ( ( ( ph -> ps ) -> ( ph -> ch ) ) ->
                 ( ( ps -> ph ) -> ( ps -> ch ) ) ) $=
    wph wps wi wph wch wi wi wps wph wch wps wph wps wi wph wch wi wps wph ax-1
    imim1i a2d $.
    $( [9-Aug-2004] $) $( [8-Aug-2004] $)

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Logical negation
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

$( This section makes our first use of the third axiom of propositonal
   calculus. $)

  ${
    a3i.1 $e |- ( -. ph -> -. ps ) $.
    $( Inference rule derived from axiom ~ ax-3 . $)
    a3i $p |- ( ps -> ph ) $=
      wph wn wps wn wi wps wph wi a3i.1 wph wps ax-3 ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    a3d.1 $e |- ( ph -> ( -. ps -> -. ch ) ) $.
    $( Deduction derived from axiom ~ ax-3 . $)
    a3d $p |- ( ph -> ( ch -> ps ) ) $=
      wph wps wn wch wn wi wch wps wi a3d.1 wps wch ax-3 syl $.
      $( [26-Mar-1995] $)
  $}

  $( From a wff and its negation, anything is true.  Theorem *2.21 of
     [WhiteheadRussell] p. 104.  Also called the Duns Scotus law. $)
  pm2.21 $p |- ( -. ph -> ( ph -> ps ) ) $=
    wph wn wps wph wph wn wps wn ax-1 a3d $.
    $( [5-Aug-1993] $)

  ${
    pm2.21i.1 $e |- -. ph $.
    $( A contradiction implies anything.  Inference from ~ pm2.21 . $)
    pm2.21i $p |- ( ph -> ps ) $=
      wps wph wph wn wps wn pm2.21i.1 a1i a3i $.
      $( [16-Sep-1993] $)
  $}

  ${
    pm2.21d.1 $e |- ( ph -> -. ps ) $.
    $( A contradiction implies anything.  Deduction from ~ pm2.21 . $)
    pm2.21d $p |- ( ph -> ( ps -> ch ) ) $=
      wph wch wps wph wps wn wch wn pm2.21d.1 a1d a3d $.
      $( [10-Feb-1996] $)
  $}

  $( Theorem *2.24 of [WhiteheadRussell] p. 104. $)
  pm2.24 $p |-  ( ph -> ( -. ph -> ps ) ) $=
    wph wn wph wps wph wps pm2.21 com12 $.
    $( [6-Jan-2005] $) $( [3-Jan-2005] $)

  ${
    pm2.24ii.1 $e |- ph $.
    pm2.24ii.2 $e |- -. ph $.
    $( A contradiction implies anything.  Inference from ~ pm2.24 . $)
    pm2.24ii $p |- ps $=
      wph wps pm2.24ii.1 wph wps pm2.24ii.2 pm2.21i ax-mp $.
      $( [27-Feb-2008] $) $( [27-Feb-2008] $)
  $}

  $( Proof by contradiction.  Theorem *2.18 of [WhiteheadRussell] p. 103.
     Also called the Law of Clavius. $)
  pm2.18 $p |- ( ( -. ph -> ph ) -> ph ) $=
    wph wn wph wi wph wph wn wph wi wph wph wn wph wi wph wn wph wph wn wph wi
    wn wph wph wn wph wi wn pm2.21 a2i a3d pm2.43i $.
    $( [5-Aug-1993] $)

  $( Peirce's axiom.  This odd-looking theorem is the "difference" between
     an intuitionistic system of propositional calculus and a classical system
     and is not accepted by intuitionists.  When Peirce's axiom is added to an
     intuitionistic system, the system becomes equivalent to our classical
     system ~ ax-1 through ~ ax-3 .  A curious fact about this
     theorem is that it requires ~ ax-3 for its proof even though the
     result has no negation connectives in it. $)
  peirce $p |- ( ( ( ph -> ps ) -> ph ) -> ph ) $=
    wph wps wi wph wi wph wn wph wi wph wph wn wph wps wi wph wph wps pm2.21
    imim1i wph pm2.18 syl $.
    $( [5-Aug-1993] $)

  $( The Inversion Axiom of the infinite-valued sentential logic (L-infinity)
     of Lukasiewicz.  Using ~ dfor2 , we can see that this essentially
     expresses "disjunction commutes."  Theorem *2.69 of [WhiteheadRussell]
     p. 108. $)
  looinv $p |- ( ( ( ph -> ps ) -> ps ) -> ( ( ps -> ph ) -> ph ) ) $=
    wph wps wi wps wi wps wph wi wph wps wi wph wi wph wph wps wi wps wph imim1
    wph wps peirce syl6 $.
    $( [20-Aug-2004] $) $( [12-Aug-2004] $)

  $( Converse of double negation.  Theorem *2.14 of [WhiteheadRussell] p. 102.
     (The proof was shortened by David Harvey, 5-Sep-99.  An even shorter
     proof found by Josh Purinton, 29-Dec-00.) $)
  nega $p |- ( -. -. ph -> ph ) $=
    wph wn wn wph wn wph wi wph wph wn wph pm2.21 wph pm2.18 syl $.
    $( [5-Aug-1993] $)

  ${
    negai.1 $e |- -. -. ph $.
    $( Inference from double negation. $)
    negai $p |- ph $=
      wph wn wn wph negai.1 wph nega ax-mp $.
      $( [27-Feb-2008] $) $( [27-Feb-2008] $)
  $}

  $( Converse of double negation.  Theorem *2.12 of [WhiteheadRussell]
     p. 101. $)
  negb $p |- ( ph -> -. -. ph ) $=
    wph wn wn wph wph wn nega a3i $.
    $( [5-Aug-1993] $)

  ${
    negbi.1 $e |- ph $.
    $( Infer double negation. $)
    negbi $p |- -. -. ph $=
      wph wph wn wn negbi.1 wph negb ax-mp $.
      $( [27-Feb-2008] $) $( [27-Feb-2008] $)
  $}

  $( Reductio ad absurdum.  Theorem *2.01 of [WhiteheadRussell] p. 100. $)
  pm2.01 $p |- ( ( ph -> -. ph ) -> -. ph ) $=
    wph wph wn wi wph wn wn wph wn wi wph wn wph wn wn wph wph wn wph nega
    imim1i wph wn pm2.18 syl $.
    $( [18-Aug-1993] $)

  ${
    pm2.01d.1 $e |- ( ph -> ( ps -> -. ps ) ) $.
    $( Deduction based on reductio ad absurdum. $)
    pm2.01d $p |- ( ph -> -. ps ) $=
      wph wps wps wn wi wps wn pm2.01d.1 wps pm2.01 syl $.
      $( [18-Aug-1993] $)
  $}

  $( Contraposition.  Theorem *2.03 of [WhiteheadRussell] p. 100. $)
  con2 $p |- ( ( ph -> -. ps ) -> ( ps -> -. ph ) ) $=
    wph wps wn wi wph wn wps wph wn wn wph wps wn wph nega imim1i a3d $.
    $( [5-Aug-1993] $)

  ${
    con2d.1 $e |- ( ph -> ( ps -> -. ch ) ) $.
    $( A contraposition deduction. $)
    con2d $p |- ( ph -> ( ch -> -. ps ) ) $=
      wph wps wch wn wi wch wps wn wi con2d.1 wps wch con2 syl $.
      $( [19-Aug-1993] $)
  $}

  $( Contraposition.  Theorem *2.15 of [WhiteheadRussell] p. 102. $)
  con1 $p |- ( ( -. ph -> ps ) -> ( -. ps -> ph ) ) $=
    wph wn wps wi wph wps wn wps wps wn wn wph wn wps negb imim2i a3d $.
    $( [5-Aug-1993] $)

  ${
    con1d.1 $e |- ( ph -> ( -. ps -> ch ) ) $.
    $( A contraposition deduction. $)
    con1d $p |- ( ph -> ( -. ch -> ps ) ) $=
      wph wps wn wch wi wch wn wps wi con1d.1 wps wch con1 syl $.
      $( [5-Aug-1993] $)
  $}

  $( Contraposition.  Theorem *2.16 of [WhiteheadRussell] p. 103. $)
  con3 $p |- ( ( ph -> ps ) -> ( -. ps -> -. ph ) ) $=
    wph wps wi wph wps wn wps wps wn wn wph wps negb imim2i con2d $.
    $( [5-Aug-1993] $)

  ${
    con3d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( A contraposition deduction. $)
    con3d $p |- ( ph -> ( -. ch -> -. ps ) ) $=
      wph wps wch wi wch wn wps wn wi con3d.1 wps wch con3 syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    con1.a $e |- ( -. ph -> ps ) $.
    $( A contraposition inference. $)
    con1i $p |- ( -. ps -> ph ) $=
      wph wps wn wph wn wps wps wn wn con1.a wps negb syl a3i $.
      $( [5-Aug-1993] $)
  $}

  ${
    con2.a $e |- ( ph -> -. ps ) $.
    $( A contraposition inference. $)
    con2i $p |- ( ps -> -. ph ) $=
      wph wn wps wph wn wn wph wps wn wph nega con2.a syl a3i $.
      $( [5-Aug-1993] $)
  $}

  ${
    con3.a $e |- ( ph -> ps ) $.
    $( A contraposition inference. $)
    con3i $p |- ( -. ps -> -. ph ) $=
      wph wn wps wph wn wn wph wps wph nega con3.a syl con1i $.
      $( [5-Aug-1993] $)
  $}

  $( This is NOT theorem *2.37 of [WhiteheadRussell] p. 105. $)
  pm2.37OLD $p |-  ( ( ps -> ch ) ->
          ( ( -. ps -> ph ) -> ( -. ph -> ch ) ) ) $=
    wps wn wph wi wps wch wi wph wn wch wi wps wn wph wi wph wn wps wch wps wph
    con1 imim1d com12 $.
    $( [23-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.5 of [WhiteheadRussell] p. 107. $)
  pm2.5 $p |-  ( -. ( ph -> ps ) -> ( -. ph -> ps ) ) $=
    wph wps wi wn wph wn wps wph wn wph wps wi wph wps pm2.21 con3i pm2.21d $.
    $( [27-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.51 of [WhiteheadRussell] p. 107. $)
  pm2.51 $p |-  ( -. ( ph -> ps ) -> ( ph -> -. ps ) ) $=
    wph wps wi wn wps wn wph wps wph wps wi wps wph ax-1 con3i a1d $.
    $( [27-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.52 of [WhiteheadRussell] p. 107. $)
  pm2.52 $p |-  ( -. ( ph -> ps ) -> ( -. ph -> -. ps ) ) $=
    wph wps wi wn wps wn wph wn wps wph wps wi wps wph ax-1 con3i a1d $.
    $( [27-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.521 of [WhiteheadRussell] p. 107. $)
  pm2.521 $p |-  ( -. ( ph -> ps ) -> ( ps -> ph ) ) $=
    wph wps wi wn wph wps wph wps pm2.52 a3d $.
    $( [6-Feb-2005] $) $( [3-Jan-2005] $)

  ${
    pm2.24i.1 $e |- ph $.
    $( Inference version of ~ pm2.24 . $)
    pm2.24i $p |- ( -. ph -> ps ) $=
      wps wph wph wps wn pm2.24i.1 a1i con1i $.
      $( [20-Aug-2001] $)
  $}

  ${
    pm2.24d.1 $e |- ( ph -> ps ) $.
    $( Deduction version of ~ pm2.21 . $)
    pm2.24d $p |- ( ph -> ( -. ps -> ch ) ) $=
      wph wch wps wph wps wch wn pm2.24d.1 a1d con1d $.
      $( [31-Jan-2006] $) $( [30-Jan-2006] $)
  $}

  ${
    mto.1 $e |- -. ps $.
    mto.2 $e |- ( ph -> ps ) $.
    $( The rule of modus tollens. $)
    mto $p |- -. ph $=
      wps wn wph wn mto.1 wph wps mto.2 con3i ax-mp $.
      $( [19-Aug-1993] $)
  $}

  ${
    mtoi.1 $e |- -. ch $.
    mtoi.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Modus tollens inference. $)
    mtoi $p |- ( ph -> -. ps ) $=
      wph wch wn wps wn mtoi.1 wph wps wch mtoi.2 con3d mpi $.
      $( [5-Jul-1994] $)
  $}

  ${
    mtod.1 $e |- ( ph -> -. ch ) $.
    mtod.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Modus tollens deduction. $)
    mtod $p |- ( ph -> -. ps ) $=
      wph wch wn wps wn mtod.1 wph wps wch mtod.2 con3d mpd $.
      $( [3-Apr-1994] $)
  $}

  ${
    mt2.1 $e |- ps $.
    mt2.2 $e |- ( ph -> -. ps ) $.
    $( A rule similar to modus tollens. $)
    mt2 $p |- -. ph $=
      wps wph wn mt2.1 wph wps mt2.2 con2i ax-mp $.
      $( [19-Aug-1993] $)
  $}

  ${
    mt2i.1 $e |- ch $.
    mt2i.2 $e |- ( ph -> ( ps -> -. ch ) ) $.
    $( Modus tollens inference. $)
    mt2i $p |- ( ph -> -. ps ) $=
      wph wch wps wn mt2i.1 wph wps wch mt2i.2 con2d mpi $.
      $( [26-Mar-1995] $)
  $}

  ${
    mt2d.1 $e |- ( ph -> ch ) $.
    mt2d.2 $e |- ( ph -> ( ps -> -. ch ) ) $.
    $( Modus tollens deduction. $)
    mt2d $p |- ( ph -> -. ps ) $=
      wph wch wps wn mt2d.1 wph wps wch mt2d.2 con2d mpd $.
      $( [4-Jul-1994] $)
  $}

  ${
    mt3.1 $e |- -. ps $.
    mt3.2 $e |- ( -. ph -> ps ) $.
    $( A rule similar to modus tollens. $)
    mt3 $p |- ph $=
      wps wn wph mt3.1 wph wps mt3.2 con1i ax-mp $.
      $( [18-May-1994] $)
  $}

  ${
    mt3i.1 $e |- -. ch $.
    mt3i.2 $e |- ( ph -> ( -. ps -> ch ) ) $.
    $( Modus tollens inference. $)
    mt3i $p |- ( ph -> ps ) $=
      wph wch wn wps mt3i.1 wph wps wch mt3i.2 con1d mpi $.
      $( [26-Mar-1995] $)
  $}

  ${
    mt3d.1 $e |- ( ph -> -. ch ) $.
    mt3d.2 $e |- ( ph -> ( -. ps -> ch ) ) $.
    $( Modus tollens deduction. $)
    mt3d $p |- ( ph -> ps ) $=
      wph wch wn wps mt3d.1 wph wps wch mt3d.2 con1d mpd $.
      $( [26-Mar-1995] $)
  $}

  ${
    mt4d.1 $e |- ( ph -> ps ) $.
    mt4d.2 $e |- ( ph -> ( -. ch -> -. ps ) ) $.
    $( Modus tollens deduction. $)
    mt4d $p |- ( ph -> ch ) $=
      wph wps wch mt4d.1 wph wch wps mt4d.2 a3d mpd $.
      $( [18-Jun-2006] $) $( [9-Jun-2006] $)
  $}

  ${
    nsyl.1 $e |- ( ph -> -. ps ) $.
    nsyl.2 $e |- ( ch -> ps ) $.
    $( A negated syllogism inference. $)
    nsyl $p |- ( ph -> -. ch ) $=
      wph wps wn wch wn nsyl.1 wch wps nsyl.2 con3i syl $.
      $( [31-Dec-1993] $)
  $}

  ${
    nsyld.1 $e |- ( ph -> ( ps -> -. ch ) ) $.
    nsyld.2 $e |- ( ph -> ( ta -> ch ) ) $.
    $( A negated syllogism deduction. $)
    nsyld $p |- ( ph -> ( ps -> -. ta ) ) $=
      wph wps wch wn wta wn nsyld.1 wph wta wch nsyld.2 con3d syld $.
      $( [10-Apr-2005] $) $( [9-Apr-2005] $)
  $}

  ${
    nsyl2.1 $e |- ( ph -> -. ps ) $.
    nsyl2.2 $e |- ( -. ch -> ps ) $.
    $( A negated syllogism inference. $)
    nsyl2 $p |- ( ph -> ch ) $=
      wph wps wn wch nsyl2.1 wch wps nsyl2.2 con1i syl $.
      $( [26-Jun-1994] $)
  $}

  ${
    nsyl3.1 $e |- ( ph -> -. ps ) $.
    nsyl3.2 $e |- ( ch -> ps ) $.
    $( A negated syllogism inference. $)
    nsyl3 $p |- ( ch -> -. ph ) $=
      wch wps wph wn nsyl3.2 wph wps nsyl3.1 con2i syl $.
      $( [1-Dec-1995] $)
  $}

  ${
    nsyl4.1 $e |- ( ph -> ps ) $.
    nsyl4.2 $e |- ( -. ph -> ch ) $.
    $( A negated syllogism inference. $)
    nsyl4 $p |- ( -. ch -> ps ) $=
      wch wn wph wps wph wch nsyl4.2 con1i nsyl4.1 syl $.
      $( [15-Feb-1996] $)
  $}

  ${
    nsyli.1 $e |- ( ph -> ( ps -> ch ) ) $.
    nsyli.2 $e |- ( th -> -. ch ) $.
    $( A negated syllogism inference. $)
    nsyli $p |- ( ph -> ( th -> -. ps ) ) $=
      wph wch wn wps wn wth wph wps wch nsyli.1 con3d nsyli.2 syl5 $.
      $( [3-May-1994] $)
  $}

  $( Theorem *3.2 of [WhiteheadRussell] p. 111, expressed with primitive
     connectives.  (The proof was shortened by Josh Purinton, 29-Dec-00.) $)
  pm3.2im $p |- ( ph -> ( ps -> -. ( ph -> -. ps ) ) ) $=
    wph wph wps wn wi wps wph wps wn pm2.27 con2d $.
    $( [5-Aug-1993] $)

  $( Theorem 8 of [Margaris] p. 60.  (The proof was shortened by Josh Purinton,
     29-Dec-00.) $)
  mth8 $p |- ( ph -> ( -. ps -> -. ( ph -> ps ) ) ) $=
    wph wph wps wi wps wph wps pm2.27 con3d $.
    $( [5-Aug-1993] $)

  $( Theorem *2.61 of [WhiteheadRussell] p. 107.  Useful for eliminating an
     antecedent.  (The proof was shortened by Mel L. O'Cat, 19-Feb-2008.) $)
  pm2.61 $p |- ( ( ph -> ps ) -> ( ( -. ph -> ps ) -> ps ) ) $=
    wph wn wps wi wph wps wi wps wn wps wi wps wph wn wps wi wps wn wph wps wph
    wps con1 imim1d wps pm2.18 syl6com $.
    $( [6-Mar-2008] $) $( [5-Aug-1993] $)

  $( Theorem *2.61 of [WhiteheadRussell] p. 107.  Useful for eliminating an
     antecedent.  (The proof was shortened by Mel L. O'Cat, 19-Feb-2008.) $)
  pm2.61-ocatOLD $p |- ( ( ph -> ps ) -> ( ( -. ph -> ps ) -> ps ) ) $=
    wph wps wi wph wn wps wi wps wn wps wi wps wps wph wps pm2.37OLD wps pm2.18
    syl6 $.
    $( [19-Feb-2008] $) $( [5-Aug-1993] $)

  $( Theorem *2.61 of [WhiteheadRussell] p. 107.  Useful for eliminating an
     antecedent. $)
  pm2.61OLD $p |- ( ( ph -> ps ) -> ( ( -. ph -> ps ) -> ps ) ) $=
    wph wps wi wps wn wph wi wps wph wn wps wi wph wps wi wps wn wph wi wps wn
    wps wi wps wph wps wps wn imim2 wps pm2.18 syl6 wph wps con1 syl5 $.
    $( [5-Aug-1993] $)

  ${
    pm2.61i.1 $e |- ( ph -> ps ) $.
    pm2.61i.2 $e |- ( -. ph -> ps ) $.
    $( Inference eliminating an antecedent. $)
    pm2.61i $p |- ps $=
      wph wps wi wph wn wps wi wps pm2.61i.1 pm2.61i.2 wph wps pm2.61 mp2 $.
      $( [5-Apr-1994] $)
  $}

  ${
    pm2.61d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    pm2.61d.2 $e |- ( ph -> ( -. ps -> ch ) ) $.
    $( Deduction eliminating an antecedent. $)
    pm2.61d $p |- ( ph -> ch ) $=
      wps wph wch wi wph wps wch pm2.61d.1 com12 wph wps wn wch pm2.61d.2 com12
      pm2.61i $.
      $( [27-Apr-1994] $)
  $}

  ${
    pm2.61d1.1 $e |- ( ph -> ( ps -> ch ) ) $.
    pm2.61d1.2 $e |- ( -. ps -> ch ) $.
    $( Inference eliminating an antecedent. $)
    pm2.61d1 $p |- ( ph -> ch ) $=
      wph wps wch pm2.61d1.1 wps wn wch wi wph pm2.61d1.2 a1i pm2.61d $.
      $( [20-Jul-2005] $) $( [15-Jul-2005] $)
  $}

  ${
    pm2.61d2.1 $e |- ( ph -> ( -. ps -> ch ) ) $.
    pm2.61d2.2 $e |- ( ps -> ch ) $.
    $( Inference eliminating an antecedent. $)
    pm2.61d2 $p |- ( ph -> ch ) $=
      wph wps wch wps wch wi wph pm2.61d2.2 a1i pm2.61d2.1 pm2.61d $.
      $( [18-Aug-1993] $)
  $}

  ${
    pm2.61ii.1 $e |- ( -. ph -> ( -. ps -> ch ) ) $.
    pm2.61ii.2 $e |- ( ph -> ch ) $.
    pm2.61ii.3 $e |- ( ps -> ch ) $.
    $( Inference eliminating two antecedents.  (The proof was shortened by Josh
       Purinton,  29-Dec-00.) $)
    pm2.61ii $p |- ch $=
      wph wch pm2.61ii.2 wph wn wps wch pm2.61ii.1 pm2.61ii.3 pm2.61d2 pm2.61i
      $.
      $( [5-Aug-1993] $)
  $}

  ${
    pm2.61nii.1 $e |- ( ph -> ( ps -> ch ) ) $.
    pm2.61nii.2 $e |- ( -. ph -> ch ) $.
    pm2.61nii.3 $e |- ( -. ps -> ch ) $.
    $( Inference eliminating two antecedents. $)
    pm2.61nii $p |- ch $=
      wps wch wps wph wch wph wps wch pm2.61nii.1 com12 pm2.61nii.2 pm2.61d1
      pm2.61nii.3 pm2.61i $.
      $( [5-Aug-1993] $)
  $}

  ${
    pm2.61iii.1 $e |- ( -. ph -> ( -. ps -> ( -. ch -> th ) ) ) $.
    pm2.61iii.2 $e |- ( ph -> th ) $.
    pm2.61iii.3 $e |- ( ps -> th ) $.
    pm2.61iii.4 $e |- ( ch -> th ) $.
    $( Inference eliminating three antecedents. $)
    pm2.61iii $p |- th $=
      wps wch wth wph wps wn wch wn wth wi wi wph wch wn wth wi wps wn wph wth
      wch wn pm2.61iii.2 a1d a1d pm2.61iii.1 pm2.61i pm2.61iii.3 pm2.61iii.4
      pm2.61ii $.
      $( [2-Jan-2002] $)
  $}

  $( Theorem *2.6 of [WhiteheadRussell] p. 107. $)
  pm2.6 $p |-  ( ( -. ph -> ps ) -> ( ( ph -> ps ) -> ps ) ) $=
    wph wps wi wph wn wps wi wps wph wps pm2.61 com12 $.
    $( [1-Feb-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.65 of [WhiteheadRussell] p. 107.  Useful for eliminating a
     consequent. $)
  pm2.65 $p |- ( ( ph -> ps ) -> ( ( ph -> -. ps ) -> -. ph ) ) $=
    wph wps wi wph wph wps wn wi wph wps wph wps wn wi wn wph wps pm3.2im a2i
    con2d $.
    $( [5-Aug-1993] $)

  ${
    pm2.65i.1 $e |- ( ph -> ps ) $.
    pm2.65i.2 $e |- ( ph -> -. ps ) $.
    $( Inference rule for proof by contradiction. $)
    pm2.65i $p |- -. ph $=
      wph wph wn wi wph wn wph wps wph pm2.65i.2 pm2.65i.1 nsyl wph pm2.01
      ax-mp $.
      $( [18-May-1994] $)
  $}

  ${
    pm2.65d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    pm2.65d.2 $e |- ( ph -> ( ps -> -. ch ) ) $.
    $( Deduction rule for proof by contradiction. $)
    pm2.65d $p |- ( ph -> -. ps ) $=
      wps wch wi wps wch wn wi wps wn wph wps wch pm2.65 pm2.65d.1 pm2.65d.2
      sylc $.
      $( [26-Jun-1994] $)
  $}

  ${
    ja.1 $e |- ( -. ph -> ch ) $.
    ja.2 $e |- ( ps -> ch ) $.
    $( Inference joining the antecedents of two premises.  (The proof was
       shortened by Mel L. O'Cat, 19-Feb-2008.) $)
    ja $p |- ( ( ph -> ps ) -> ch ) $=
      wph wps wi wph wch wps wch wph ja.2 imim2i ja.1 pm2.61d1 $.
      $( [19-Feb-2008] $) $( [5-Aug-1993] $)

    $( Inference joining the antecedents of two premises.  (The proof was
       shortened by Mel L. O'Cat, 30-Aug-2004.) $)
    jaOLD $p |- ( ( ph -> ps ) -> ch ) $=
      wph wph wps wi wch wi wph wph wps wi wps wch wph wps pm2.27 ja.2 syl6 wph
      wn wch wph wps wi ja.1 a1d pm2.61i $.
      $( [30-Aug-2004] $) $( [5-Aug-1993] $)
  $}

  ${
    jc.1 $e |- ( ph -> ps ) $.
    jc.2 $e |- ( ph -> ch ) $.
    $( Inference joining the consequents of two premises. $)
    jc $p |- ( ph -> -. ( ps -> -. ch ) ) $=
      wps wch wps wch wn wi wn wph wps wch pm3.2im jc.1 jc.2 sylc $.
      $( [5-Aug-1993] $)
  $}

  $( Simplification.  Similar to Theorem *3.26 (Simp) of [WhiteheadRussell]
     p. 112. $)
  pm3.26im $p |- ( -. ( ph -> -. ps ) -> ph ) $=
    wph wph wps wn wi wph wps wn pm2.21 con1i $.
    $( [5-Aug-1993] $)

  $( Simplification.  Similar to Theorem *3.27 (Simp) of [WhiteheadRussell]
     p. 112. $)
  pm3.27im $p |- ( -. ( ph -> -. ps ) -> ps ) $=
    wps wph wps wn wi wps wn wph ax-1 con1i $.
    $( [5-Aug-1993] $)

  $( Importation theorem expressed with primitive connectives. $)
  impt $p |- ( ( ph -> ( ps -> ch ) ) -> ( -. ( ph -> -. ps ) -> ch ) ) $=
    wph wps wch wi wi wch wph wps wn wi wph wps wch wi wi wph wch wn wps wn wps
    wch wi wch wn wps wn wi wph wps wch con3 imim2i com23 con1d $.
    $( [25-Apr-1994] $)

  $( Exportation theorem expressed with primitive connectives. $)
  expt $p |- ( ( -. ( ph -> -. ps ) -> ch ) -> ( ph -> ( ps -> ch ) ) ) $=
    wph wph wps wn wi wn wch wi wps wch wi wph wps wph wps wn wi wn wch wph wps
    pm3.2im imim1d com12 $.
    $( [5-Aug-1993] $)

  ${
    impi.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( An importation inference. $)
    impi $p |- ( -. ( ph -> -. ps ) -> ch ) $=
      wph wps wch wi wi wph wps wn wi wn wch wi impi.1 wph wps wch impt ax-mp
      $.
      $( [5-Aug-1993] $)
  $}

  ${
    expi.1 $e |- ( -. ( ph -> -. ps ) -> ch ) $.
    $( An exportation inference. $)
    expi $p |- ( ph -> ( ps -> ch ) ) $=
      wph wps wn wi wn wch wi wph wps wch wi wi expi.1 wph wps wch expt ax-mp
      $.
      $( [5-Aug-1993] $)
  $}

  $( Theorem used to justify definition of biconditional ~ def-bi .  (The proof
     was shortened by Josh Purinton, 29-Dec-00.) $)
  bijust $p |- -. ( ( ph -> ph ) -> -. ( ph -> ph ) ) $=
    wph wph wi wph wph wi wn wi wph wph wi wph id wph wph wi pm2.01 mt2 $.
    $( [11-May-1999] $)

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Logical equivalence
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

  $( Declare the biconditional connective. $)
  $c <-> $. $( Double arrow (read:  'if and only if' or
               'is logically equivalent to') $)

  $( Extend our wff definition to include the biconditional connective. $)
  wb $a wff ( ph <-> ps ) $.

  $( This is our first definition, which introduces and defines the
     biconditional connective ` <-> ` .  We define a wff of the form
     ` ( ph <-> ps ) ` as an abbreviation for
     ` -. ( ( ph -> ps ) -> -. ( ps -> ph ) ) ` .

     Unlike most traditional developments, we have chosen not to have a
     separate symbol such as "Df." to mean "is defined as."  Instead, we will
     later use the biconditional connective for this purpose ( ~ df-or is its
     first use), as it allows us to use logic to manipulate definitions
     directly.  This greatly simplifies many proofs since it eliminates the
     need for a separate mechanism for introducing and eliminating
     definitions.  Of course, we cannot use this mechanism to define the
     biconditional itself, since it hasn't been introduced yet.

     In its most general form, a definition is simply an assertion that
     introduces a new symbol (or a new combination of existing symbols, as in
     ~ df-3an ) that is eliminable and does not strengthen the existing
     language.  The latter requirement means that the set of provable
     statements not containing the new symbol (or new combination) should
     remain exactly the same after the definition is introduced.  Our
     definition of the biconditional may look unusual compared to most
     definitions, but it strictly satisfies these requirements.

     The justification for our definition is that if we mechanically replace
     the first wff above (the definiendum i.e. the thing being defined) with
     the second (the definiens i.e. the defining expression) in the
     definition, the definition becomes a substitution instance of previously
     proved theorem ~ bijust .  It is impossible to use ~ def-bi to prove any
     statement expressed in the original language that can't be proved from
     the original axioms.  For if it were, we could replace it with instances
     of ~ bijust throughout the proof, thus obtaining a proof from the
     original axioms (contradiction).

     Note that from Metamath's point of view, a definition is just another
     axiom - i.e. an assertion we claim to be true - but from our high level
     point of view, we are are not strengthening the language.  To indicate
     this fact, we prefix definition labels with "df-" instead of "ax-".
     (This prefixing is an informal convention that means nothing to the
     Metamath proof verifier; it is just for human readability.)

     See ~ bii and ~ bi for theorems suggesting the typical textbook
     definition of ` <-> ` , showing that our definition has the properties
     we expect.  $)
  def-bi $a |- -. ( ( ( ph <-> ps ) -> -. ( ( ph -> ps ) -> -. ( ps -> ph ) ) )
        -> -. ( -. ( ( ph -> ps ) -> -. ( ps -> ph ) ) -> ( ph <-> ps ) ) ) $.

  $( Property of the biconditional connective. $)
  bi1 $p |- ( ( ph <-> ps ) -> ( ph -> ps ) ) $=
    wph wps wb wph wps wi wps wph wi wn wi wn wph wps wi wph wps wb wph wps wi
    wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi
    wn wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps def-bi wph wps wb
    wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb
    wi pm3.26im ax-mp wph wps wi wps wph wi pm3.26im syl $.
    $( [11-May-1999] $)

  $( Property of the biconditional connective. $)
  bi2 $p |- ( ( ph <-> ps ) -> ( ps -> ph ) ) $=
    wph wps wb wph wps wi wps wph wi wn wi wn wps wph wi wph wps wb wph wps wi
    wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi
    wn wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps def-bi wph wps wb
    wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb
    wi pm3.26im ax-mp wph wps wi wps wph wi pm3.27im syl $.
    $( [11-May-1999] $)

  $( Property of the biconditional connective. $)
  bi3 $p |- ( ( ph -> ps ) -> ( ( ps -> ph ) -> ( ph <-> ps ) ) ) $=
    wph wps wi wps wph wi wph wps wb wph wps wb wph wps wi wps wph wi wn wi wn
    wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wph wps wi wps wph
    wi wn wi wn wph wps wb wi wph wps def-bi wph wps wb wph wps wi wps wph wi wn
    wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi pm3.27im ax-mp expi
    $.
    $( [11-May-1999] $)

  ${
    biimp.1 $e |- ( ph <-> ps ) $.
    $( Infer an implication from a logical equivalence. $)
    biimp $p |- ( ph -> ps ) $=
      wph wps wb wph wps wi biimp.1 wph wps bi1 ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    biimpr.1 $e |- ( ph <-> ps ) $.
    $( Infer a converse implication from a logical equivalence. $)
    biimpr $p |- ( ps -> ph ) $=
      wph wps wb wps wph wi biimpr.1 wph wps bi2 ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    biimpd.1 $e |- ( ph -> ( ps <-> ch ) ) $.

    $( Deduce an implication from a logical equivalence. $)
    biimpd $p |- ( ph -> ( ps -> ch ) ) $=
      wph wps wch wb wps wch wi biimpd.1 wps wch bi1 syl $.
      $( [5-Aug-1993] $)

   $( Deduce a converse implication from a logical equivalence. $)
    biimprd $p |- ( ph -> ( ch -> ps ) ) $=
      wph wps wch wb wch wps wi biimpd.1 wps wch bi2 syl $.
      $( [5-Aug-1993] $)

   $( Deduce a commuted implication from a logical equivalence. $)
    biimpcd $p |- ( ps -> ( ph -> ch ) ) $=
      wph wps wch wph wps wch biimpd.1 biimpd com12 $.
      $( [3-May-1994] $)

   $( Deduce a converse commuted implication from a logical equivalence. $)
    biimprcd $p |- ( ch -> ( ph -> ps ) ) $=
      wph wch wps wph wps wch biimpd.1 biimprd com12 $.
      $( [3-May-1994] $)
  $}

  ${
    impbi.1 $e |- ( ph -> ps ) $.
    impbi.2 $e |- ( ps -> ph ) $.
    $( Infer an equivalence from an implication and its converse. $)
    impbi $p |- ( ph <-> ps ) $=
      wph wps wi wps wph wi wph wps wb impbi.1 impbi.2 wph wps bi3 mp2 $.
      $( [5-Aug-1993] $)
  $}

  $( Relate the biconditional connective to primitive connectives.  See ~ biigb
     for an unusual version proved directly from axioms. $)
  bii $p |- ( ( ph <-> ps ) <-> -. ( ( ph -> ps ) -> -. ( ps -> ph ) ) ) $=
    wph wps wb wph wps wi wps wph wi wn wi wn wph wps wb wph wps wi wps wph wi
    wph wps bi1 wph wps bi2 jc wph wps wi wps wph wi wph wps wb wph wps bi3
    impi impbi $.
    $( [5-Aug-1993] $)

  $( This proof of ~ bii , discovered by Gregory Bush on 8-Mar-2004, has
     several curious properties.  First, it has only 17 steps directly
     from the axioms and ~ def-bi , compared to over 800 steps were the proof
     of ~ bii expanded into axioms.  Second, step 2 demands only the property
     of "true"; any axiom (or theorem) could be used.  It might be thought,
     therefore, that it is in some sense redundant, but in fact no proof
     is shorter than this (measured by number of steps).  Third, it illustrates
     how intermediate steps can "blow up" in size even in short proofs.
     Fourth, the compressed proof is only 182 bytes (or 17 bytes in D-proof
     notation), but the generated web page is over 200kB with intermediate
     steps that are essentially incomprehensible to humans (other than Gregory
     Bush).  If there were an obfuscated code contest for proofs, this would be
     a contender. $)
  biigb $p |- ( ( ph <-> ps ) <-> -. ( ( ph -> ps ) -> -. ( ps -> ph ) ) ) $=
    wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn
    wph wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb wph wps
    def-bi wch wth wch wi wi wph wps wb wph wps wi wps wph wi wn wi wn wi wph
    wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wph wps wb wph wps wi wps
    wph wi wn wi wn wb wi wch wth ax-1 wph wps wb wph wps wi wps wph wi wn wi
    wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wph wps wb wph
    wps wi wps wph wi wn wi wn wb wi wn wch wth wch wi wi wn wi wch wth wch wi
    wi wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi
    wn wph wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb wi
    wi wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi
    wn wph wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb wi
    wn wph wps wb wph wps wi wps wph wi wn wi wn wb wph wps wb wph wps wi wps
    wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wi
    wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn
    wph wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb wi wn
    wi wi wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn
    wi wn wph wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb
    wi wn wch wth wch wi wi wn wi wph wps wb wph wps wi wps wph wi wn wi wn wi
    wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wph wps wb wph wps wi
    wps wph wi wn wi wn wb wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb
    wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn
    wph wps wb wi wn wi wn wi ax-1 wph wps wb wph wps wi wps wph wi wn wi wn wi
    wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wph wps wb wph wps wi
    wps wph wi wn wi wn wb wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb
    wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn
    wph wps wb wi wn wi wn wi wph wps wb wph wps wi wps wph wi wn wi wn wi wph
    wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wph wps wb wph wps wi wps
    wph wi wn wi wn wb wi wn wi wch wth wch wi wi wn wi wi wph wps wb wph wps
    wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn
    wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb wi wn wph wps wb wph wps
    wi wps wph wi wn wi wn wb wph wps wb wph wps wi wps wph wi wn wi wn wi wph
    wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wi wph wps wb wph wps wi
    wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi
    wn wph wps wb wph wps wi wps wph wi wn wi wn wb wi wn wi wi wph wps wb wph
    wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi
    wn wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb wi wn wch wth wch wi
    wi wn wi wi wph wps wb wph wps wi wps wph wi wn wi wn wb wph wps wb wph wps
    wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn
    wi wn wi wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi
    wn wi wn wph wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn wi wn
    wb wi wn wi wch wth wch wi wi wn wi wph wps wb wph wps wi wps wph wi wn wi
    wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wph wps wb wph
    wps wi wps wph wi wn wi wn wb wi wn wph wps wb wph wps wi wps wph wi wn wi
    wn wb wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn
    wi wn wph wps wb wi wn wi wn wi wph wps wb wph wps wi wps wph wi wn wi wn
    wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wph wps wb wph wps
    wi wps wph wi wn wi wn wb wi wn wi wch wth wch wi wi wn wi wi wch wth wch
    wi wi wn wn wph wps wb wph wps wi wps wph wi wn wi wn wb wph wps wb wph wps
    wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn
    wi wn wi wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi
    wn wi wn wph wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn wi wn
    wb wi wn wi wn wi wph wps wb wph wps wi wps wph wi wn wi wn wb wph wps wb
    wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb
    wi wn wi wn wi wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps
    wph wi wn wi wn wph wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn
    wi wn wb wi wn wi wch wth wch wi wi wn wi wph wps wb wph wps wi wps wph wi
    wn wi wn wb wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph
    wi wn wi wn wph wps wb wi wn wi wn wi wph wps wb wph wps wi wps wph wi wn
    wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wph wps wb
    wph wps wi wps wph wi wn wi wn wb wi wn wi wn wch wth wch wi wi wn wn wph
    wps wb wph wps wi wps wph wi wn wi wn wb wph wps wb wph wps wi wps wph wi
    wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wi wph
    wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph
    wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb wi wn wi wn
    wi wph wps wb wph wps wi wps wph wi wn wi wn def-bi wph wps wb wph wps wi
    wps wph wi wn wi wn wb wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps
    wi wps wph wi wn wi wn wph wps wb wi wn wi wn wi wph wps wb wph wps wi wps
    wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn
    wph wps wb wph wps wi wps wph wi wn wi wn wb wi wn wi wn wch wth wch wi wi
    wn wn ax-1 ax-mp wch wth wch wi wi wn wph wps wb wph wps wi wps wph wi wn
    wi wn wb wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi
    wn wi wn wph wps wb wi wn wi wn wi wph wps wb wph wps wi wps wph wi wn wi
    wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wph wps wb wph
    wps wi wps wph wi wn wi wn wb wi wn wi ax-3 ax-mp wph wps wb wph wps wi wps
    wph wi wn wi wn wb wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi
    wps wph wi wn wi wn wph wps wb wi wn wi wn wi wph wps wb wph wps wi wps wph
    wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn wph
    wps wb wph wps wi wps wph wi wn wi wn wb wi wn wi wch wth wch wi wi wn wi
    wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn
    wph wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb wi wn
    ax-1 ax-mp wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph
    wi wn wi wn wph wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn wi
    wn wb wi wn wph wps wb wph wps wi wps wph wi wn wi wn wb wph wps wb wph wps
    wi wps wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn
    wi wn wi wph wps wb wph wps wi wps wph wi wn wi wn wi wph wps wi wps wph wi
    wn wi wn wph wps wb wi wn wi wn wph wps wb wph wps wi wps wph wi wn wi wn
    wb wi wn wi wch wth wch wi wi wn ax-2 ax-mp ax-mp wph wps wb wph wps wi wps
    wph wi wn wi wn wi wph wps wi wps wph wi wn wi wn wph wps wb wi wn wi wn
    wph wps wb wph wps wi wps wph wi wn wi wn wb wi wch wth wch wi wi ax-3
    ax-mp ax-mp ax-mp $.
    $( [10-Mar-2004] $) $( [10-Mar-2004] $)

  $( Logical equivalence of commuted antecedents.  Part of Theorem *4.87 of
     [WhiteheadRussell] p. 122. $)
  bi2.04 $p |- ( ( ph -> ( ps -> ch ) ) <-> ( ps -> ( ph -> ch ) ) ) $=
    wph wps wch wi wi wps wph wch wi wi wph wps wch pm2.04 wps wph wch pm2.04
    impbi $.
    $( [5-Aug-1993] $)

  $( Double negation.  Theorem *4.13 of [WhiteheadRussell] p. 117. $)
  pm4.13 $p |- ( ph <-> -. -. ph ) $=
    wph wph wn wn wph negb wph nega impbi $.
    $( [5-Aug-1993] $)

  $( Theorem *4.8 of [WhiteheadRussell] p. 122. $)
  pm4.8 $p |-  ( ( ph -> -. ph ) <-> -. ph ) $=
    wph wph wn wi wph wn wph pm2.01 wph wn wph ax-1 impbi $.
    $( [5-Feb-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.81 of [WhiteheadRussell] p. 122. $)
  pm4.81 $p |-  ( ( -. ph -> ph ) <-> ph ) $=
    wph wn wph wi wph wph pm2.18 wph wph pm2.24 impbi $.
    $( [10-Feb-2005] $) $( [3-Jan-2005] $)

  $( Contraposition.  Theorem *4.1 of [WhiteheadRussell] p. 116. $)
  pm4.1 $p |- ( ( ph -> ps ) <-> ( -. ps -> -. ph ) ) $=
    wph wps wi wps wn wph wn wi wph wps con3 wps wph ax-3 impbi $.
    $( [5-Aug-1993] $)

  $( Contraposition.  Bidirectional version of ~ con2 . $)
  bi2.03 $p |- ( ( ph -> -. ps ) <-> ( ps -> -. ph ) ) $=
    wph wps wn wi wps wph wn wi wph wps con2 wps wph con2 impbi $.
    $( [5-Aug-1993] $)

  $( Contraposition.  Bidirectional version of ~ con1 . $)
  bi2.15 $p |- ( ( -. ph -> ps ) <-> ( -. ps -> ph ) ) $=
    wph wn wps wi wps wn wph wi wph wps con1 wps wph con1 impbi $.
    $( [5-Aug-1993] $)

  $( Antecedent absorption implication.  Theorem *5.4 of
     [WhiteheadRussell] p. 125. $)
  pm5.4 $p |- ( ( ph -> ( ph -> ps ) ) <-> ( ph -> ps ) ) $=
    wph wph wps wi wi wph wps wi wph wps pm2.43 wph wps wi wph ax-1 impbi $.
    $( [5-Aug-1993] $)

  $( Distributive law for implication.  Compare Theorem *5.41 of
     [WhiteheadRussell] p. 125. $)
  imdi $p |- ( ( ph -> ( ps -> ch ) ) <->
               ( ( ph -> ps ) -> ( ph -> ch ) ) ) $=
    wph wps wch wi wi wph wps wi wph wch wi wi wph wps wch ax-2 wph wps wch
    pm2.86 impbi $.
    $( [5-Aug-1993] $)

  $( Theorem *5.41 of [WhiteheadRussell] p. 125. $)
  pm5.41 $p |-  ( ( ( ph -> ps ) -> ( ph -> ch ) ) <->
                ( ph -> ( ps -> ch ) ) ) $=
    wph wps wi wph wch wi wi wph wps wch wi wi wph wps wch pm2.86 wph wps wch
    ax-2 impbi $.
    $( [10-Feb-2005] $) $( [3-Jan-2005] $)

  $( Principle of identity for logical equivalence.  Theorem *4.2 of
     [WhiteheadRussell] p. 117. $)
  pm4.2 $p |- ( ph <-> ph ) $=
    wph wph wph id wph id impbi $.
    $( [5-Aug-1993] $)

  $( Principle of identity with antecedent. $)
  pm4.2i $p |- ( ph -> ( ps <-> ps ) ) $=
    wps wps wb wph wps pm4.2 a1i $.
    $( [25-Nov-1995] $)

  ${
    bicom.1 $e |- ( ph <-> ps ) $.
    $( Inference from commutative law for logical equivalence. $)
    bicomi $p |- ( ps <-> ph ) $=
      wps wph wph wps bicom.1 biimpr wph wps bicom.1 biimp impbi $.
      $( [5-Aug-1993] $)
  $}

  ${
    bitr.1 $e |- ( ph <-> ps ) $.
    bitr.2 $e |- ( ps <-> ch ) $.
    $( An inference from transitive law for logical equivalence. $)
    bitr $p |- ( ph <-> ch ) $=
      wph wch wph wps wch wph wps bitr.1 biimp wps wch bitr.2 biimp syl wch wps
      wph wps wch bitr.2 biimpr wph wps bitr.1 biimpr syl impbi $.
      $( [5-Aug-1993] $)
  $}

  ${
    bitr2.1 $e |- ( ph <-> ps ) $.
    bitr2.2 $e |- ( ps <-> ch ) $.
    $( An inference from transitive law for logical equivalence. $)
    bitr2 $p |- ( ch <-> ph ) $=
      wph wch wph wps wch bitr2.1 bitr2.2 bitr bicomi $.
      $( [5-Aug-1993] $)
  $}

  ${
    bitr3.1 $e |- ( ps <-> ph ) $.
    bitr3.2 $e |- ( ps <-> ch ) $.
    $( An inference from transitive law for logical equivalence. $)
    bitr3 $p |- ( ph <-> ch ) $=
      wph wps wch wps wph bitr3.1 bicomi bitr3.2 bitr $.
      $( [5-Aug-1993] $)
  $}

  ${
    bitr4.1 $e |- ( ph <-> ps ) $.
    bitr4.2 $e |- ( ch <-> ps ) $.
    $( An inference from transitive law for logical equivalence. $)
    bitr4 $p |- ( ph <-> ch ) $=
      wph wps wch bitr4.1 wch wps bitr4.2 bicomi bitr $.
      $( [5-Aug-1993] $)
  $}

  ${
    3bitr.1 $e |- ( ph <-> ps ) $.
    3bitr.2 $e |- ( ps <-> ch ) $.
    3bitr.3 $e |- ( ch <-> th ) $.
    $( A chained inference from transitive law for logical equivalence. $)
    3bitr $p |- ( ph <-> th ) $=
      wph wps wth 3bitr.1 wps wch wth 3bitr.2 3bitr.3 bitr bitr $.
      $( [5-Aug-1993] $)

    $( A chained inference from transitive law for logical equivalence. $)
    3bitrr $p |- ( th <-> ph ) $=
      wth wch wph 3bitr.3 wph wps wch 3bitr.1 3bitr.2 bitr2 bitr3 $.
      $( [10-Aug-2006] $) $( [4-Aug-2006] $)
  $}

  ${
    3bitr2.1 $e |- ( ph <-> ps ) $.
    3bitr2.2 $e |- ( ch <-> ps ) $.
    3bitr2.3 $e |- ( ch <-> th ) $.
    $( A chained inference from transitive law for logical equivalence. $)
    3bitr2 $p |- ( ph <-> th ) $=
      wph wch wth wph wps wch 3bitr2.1 3bitr2.2 bitr4 3bitr2.3 bitr $.
      $( [10-Aug-2006] $) $( [4-Aug-2006] $)

    $( A chained inference from transitive law for logical equivalence. $)
    3bitr2r $p |- ( th <-> ph ) $=
      wph wch wth wph wps wch 3bitr2.1 3bitr2.2 bitr4 3bitr2.3 bitr2 $.
      $( [10-Aug-2006] $) $( [4-Aug-2006] $)
  $}

  ${
    3bitr3.1 $e |- ( ph <-> ps ) $.
    3bitr3.2 $e |- ( ph <-> ch ) $.
    3bitr3.3 $e |- ( ps <-> th ) $.
    $( A chained inference from transitive law for logical equivalence. $)
    3bitr3 $p |- ( ch <-> th ) $=
      wch wps wth wch wph wps 3bitr3.2 3bitr3.1 bitr3 3bitr3.3 bitr $.
      $( [19-Aug-1993] $)

    $( A chained inference from transitive law for logical equivalence. $)
    3bitr3r $p |- ( th <-> ch ) $=
      wth wps wch 3bitr3.3 wps wph wch 3bitr3.1 3bitr3.2 bitr3 bitr3 $.
      $( [5-Aug-1993] $)
  $}

  ${
    3bitr4.1 $e |- ( ph <-> ps ) $.
    3bitr4.2 $e |- ( ch <-> ph ) $.
    3bitr4.3 $e |- ( th <-> ps ) $.
    $( A chained inference from transitive law for logical equivalence.  This
       inference is frequently used to apply a definition to both sides of a
       logical equivalence. $)
    3bitr4 $p |- ( ch <-> th ) $=
      wch wph wth 3bitr4.2 wph wps wth 3bitr4.1 3bitr4.3 bitr4 bitr $.
      $( [5-Aug-1993] $)

    $( A chained inference from transitive law for logical equivalence. $)
    3bitr4r $p |- ( th <-> ch ) $=
      wch wph wth 3bitr4.2 wph wps wth 3bitr4.1 3bitr4.3 bitr4 bitr2 $.
      $( [2-Sep-1995] $)
  $}

  $( The next three rules are useful for building up wff's around a
     definition, in order to make use of the definition. $)

  ${
    bi.a $e |- ( ph <-> ps ) $.

    $( Introduce an antecedent to both sides of a logical equivalence. $)
    imbi2i $p |- ( ( ch -> ph ) <-> ( ch -> ps ) ) $=
      wch wph wi wch wps wi wph wps wch wph wps bi.a biimp imim2i wps wph wch
      wph wps bi.a biimpr imim2i impbi $.
      $( [5-Aug-1993] $)

    $( Introduce a consequent to both sides of a logical equivalence. $)
    imbi1i $p |- ( ( ph -> ch ) <-> ( ps -> ch ) ) $=
      wph wch wi wps wch wi wps wph wch wph wps bi.a biimpr imim1i wph wps wch
      wph wps bi.a biimp imim1i impbi $.
      $( [5-Aug-1993] $)

    $( Negate both sides of a logical equivalence. $)
    negbii $p |- ( -. ph <-> -. ps ) $=
      wph wn wps wn wps wph wph wps bi.a biimpr con3i wph wps wph wps bi.a
      biimp con3i impbi $.
      $( [5-Aug-1993] $)

  $}

  ${
    imbi12i.1 $e |- ( ph <-> ps ) $.
    imbi12i.2 $e |- ( ch <-> th ) $.
    $( Join two logical equivalences to form equivalence of implications. $)
    imbi12i $p |- ( ( ph -> ch ) <-> ( ps -> th ) ) $=
      wph wch wi wph wth wi wps wth wi wch wth wph imbi12i.2 imbi2i wph wps wth
      imbi12i.1 imbi1i bitr $.
      $( [5-Aug-1993] $)
  $}

  ${
    mpbi.min $e |- ph $.
    mpbi.maj $e |- ( ph <-> ps ) $.
    $( An inference from a biconditional, related to modus ponens. $)
    mpbi $p |- ps $=
      wph wps mpbi.min wph wps mpbi.maj biimp ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    mpbir.min $e |- ps $.
    mpbir.maj $e |- ( ph <-> ps ) $.
    $( An inference from a biconditional, related to modus ponens. $)
    mpbir $p |- ph $=
      wps wph mpbir.min wph wps mpbir.maj biimpr ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    mtbi.1 $e |- -. ph $.
    mtbi.2 $e |- ( ph <-> ps ) $.
    $( An inference from a biconditional, related to modus tollens. $)
    mtbi $p |- -. ps $=
      wph wn wps wn mtbi.1 wph wps mtbi.2 negbii mpbi $.
      $( [15-Nov-1994] $)
  $}

  ${
    mtbir.1 $e |- -. ps $.
    mtbir.2 $e |- ( ph <-> ps ) $.
    $( An inference from a biconditional, related to modus tollens. $)
    mtbir $p |- -. ph $=
      wph wn wps wn mtbir.1 wph wps mtbir.2 negbii mpbir $.
      $( [15-Nov-1994] $)
  $}

  ${
    mpbii.min $e |- ps $.
    mpbii.maj $e |- ( ph -> ( ps <-> ch ) ) $.
    $( An inference from a nested biconditional, related to modus ponens. $)
    mpbii $p |- ( ph -> ch ) $=
      wph wps wch mpbii.min wph wps wch mpbii.maj biimpd mpi $.
      $( [5-Aug-1993] $)
  $}

  ${
    mpbiri.min $e |- ch $.
    mpbiri.maj $e |- ( ph -> ( ps <-> ch ) ) $.
    $( An inference from a nested biconditional, related to modus ponens. $)
    mpbiri $p |- ( ph -> ps ) $=
      wph wch wps mpbiri.min wph wps wch mpbiri.maj biimprd mpi $.
      $( [5-Aug-1993] $)
  $}

  ${
    mpbid.min $e |- ( ph -> ps ) $.
    mpbid.maj $e |- ( ph -> ( ps <-> ch ) ) $.
    $( A deduction from a biconditional, related to modus ponens. $)
    mpbid $p |- ( ph -> ch ) $=
      wph wps wch mpbid.min wph wps wch mpbid.maj biimpd mpd $.
      $( [5-Aug-1993] $)
  $}

  ${
    mpbird.min $e |- ( ph -> ch ) $.
    mpbird.maj $e |- ( ph -> ( ps <-> ch ) ) $.
    $( A deduction from a biconditional, related to modus ponens. $)
    mpbird $p |- ( ph -> ps ) $=
      wph wch wps mpbird.min wph wps wch mpbird.maj biimprd mpd $.
      $( [5-Aug-1993] $)
  $}

  ${
    a1bi.1 $e |- ph $.
    $( Inference rule introducing a theorem as an antecedent. $)
    a1bi $p |- ( ps <-> ( ph -> ps ) ) $=
      wps wph wps wi wps wph ax-1 wph wph wps wi wps wi a1bi.1 wph wps pm2.27
      ax-mp impbi $.
      $( [5-Aug-1993] $)
  $}

  ${
    sylib.1 $e |- ( ph -> ps ) $.
    sylib.2 $e |- ( ps <-> ch ) $.
    $( A mixed syllogism inference from an implication and a biconditional. $)
    sylib $p |- ( ph -> ch ) $=
      wph wps wch sylib.1 wps wch sylib.2 biimp syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    sylbi.1 $e |- ( ph <-> ps ) $.
    sylbi.2 $e |- ( ps -> ch ) $.
    $( A mixed syllogism inference from a biconditional and an implication.
       Useful for substituting an antecedent with a definition. $)
    sylbi $p |- ( ph -> ch ) $=
      wph wps wch wph wps sylbi.1 biimp sylbi.2 syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    sylibr.1 $e |- ( ph -> ps ) $.
    sylibr.2 $e |- ( ch <-> ps ) $.
    $( A mixed syllogism inference from an implication and a biconditional.
       Useful for substituting a consequent with a definition. $)
    sylibr $p |- ( ph -> ch ) $=
      wph wps wch sylibr.1 wch wps sylibr.2 biimpr syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    sylbir.1 $e |- ( ps <-> ph ) $.
    sylbir.2 $e |- ( ps -> ch ) $.
    $( A mixed syllogism inference from a biconditional and an implication. $)
    sylbir $p |- ( ph -> ch ) $=
      wph wps wch wps wph sylbir.1 biimpr sylbir.2 syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    sylibd.1 $e |- ( ph -> ( ps -> ch ) ) $.
    sylibd.2 $e |- ( ph -> ( ch <-> th ) ) $.
    $( A syllogism deduction. $)
    sylibd $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth sylibd.1 wph wch wth sylibd.2 biimpd syld $.
      $( [3-Aug-1994] $)
  $}

  ${
    sylbid.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    sylbid.2 $e |- ( ph -> ( ch -> th ) ) $.
    $( A syllogism deduction. $)
    sylbid $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth wph wps wch sylbid.1 biimpd sylbid.2 syld $.
      $( [3-Aug-1994] $)
  $}

  ${
    sylibrd.1 $e |- ( ph -> ( ps -> ch ) ) $.
    sylibrd.2 $e |- ( ph -> ( th <-> ch ) ) $.
    $( A syllogism deduction. $)
    sylibrd $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth sylibrd.1 wph wth wch sylibrd.2 biimprd syld $.
      $( [3-Aug-1994] $)
  $}

  ${
    sylbird.1 $e |- ( ph -> ( ch <-> ps ) ) $.
    sylbird.2 $e |- ( ph -> ( ch -> th ) ) $.
    $( A syllogism deduction. $)
    sylbird $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth wph wch wps sylbird.1 biimprd sylbird.2 syld $.
      $( [3-Aug-1994] $)
  $}

  ${
    syl5ib.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl5ib.2 $e |- ( th <-> ps ) $.
    $( A mixed syllogism inference from a nested implication and a
       biconditional.  Useful for substituting an embedded antecedent with a
       definition. $)
    syl5ib $p |- ( ph -> ( th -> ch ) ) $=
      wph wps wch wth syl5ib.1 wth wps syl5ib.2 biimp syl5 $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl5ibr.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl5ibr.2 $e |- ( ps <-> th ) $.
    $( A mixed syllogism inference from a nested implication and a
       biconditional. $)
    syl5ibr $p |- ( ph -> ( th -> ch ) ) $=
      wph wps wch wth syl5ibr.1 wps wth syl5ibr.2 biimpr syl5 $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl5bi.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl5bi.2 $e |- ( th -> ps ) $.
    $( A mixed syllogism inference. $)
    syl5bi $p |- ( ph -> ( th -> ch ) ) $=
      wph wps wch wth wph wps wch syl5bi.1 biimpd syl5bi.2 syl5 $.
      $( [5-Aug-1993] $)

    $( A mixed syllogism inference. $)
    syl5cbi $p |- ( th -> ( ph -> ch ) ) $=
      wph wth wch wph wps wch wth syl5bi.1 syl5bi.2 syl5bi com12 $.
      $( [22-Jun-2007] $) $( [19-Jun-2007] $)
  $}

  ${
    syl5bir.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl5bir.2 $e |- ( th -> ch ) $.
    $( A mixed syllogism inference. $)
    syl5bir $p |- ( ph -> ( th -> ps ) ) $=
      wph wch wps wth wph wps wch syl5bir.1 biimprd syl5bir.2 syl5 $.
      $( [3-Apr-1994] $)

    $( A mixed syllogism inference. $)
    syl5cbir $p |- ( th -> ( ph -> ps ) ) $=
      wph wth wps wph wps wch wth syl5bir.1 syl5bir.2 syl5bir com12 $.
      $( [20-Jun-2007] $) $( [20-Jun-2007] $)
  $}

  ${
    syl6ib.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl6ib.2 $e |- ( ch <-> th ) $.
    $( A mixed syllogism inference from a nested implication and a
       biconditional. $)
    syl6ib $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth syl6ib.1 wch wth syl6ib.2 biimp syl6 $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl6ibr.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl6ibr.2 $e |- ( th <-> ch ) $.
    $( A mixed syllogism inference from a nested implication and a
       biconditional.  Useful for substituting an embedded consequent with a
       definition. $)
    syl6ibr $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth syl6ibr.1 wth wch syl6ibr.2 biimpr syl6 $.
      $( [5-Aug-1993] $)
  $}


  ${
    syl6bi.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl6bi.2 $e |- ( ch -> th ) $.
    $( A mixed syllogism inference. $)
    syl6bi $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth wph wps wch syl6bi.1 biimpd syl6bi.2 syl6 $.
      $( [2-Jan-1994] $)
  $}

  ${
    syl6bir.1 $e |- ( ph -> ( ch <-> ps ) ) $.
    syl6bir.2 $e |- ( ch -> th ) $.
    $( A mixed syllogism inference. $)
    syl6bir $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth wph wch wps syl6bir.1 biimprd syl6bir.2 syl6 $.
      $( [18-May-1994] $)
  $}

  ${
    syl7ib.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl7ib.2 $e |- ( ta <-> ch ) $.
    $( A mixed syllogism inference from a doubly nested implication and a
       biconditional. $)
    syl7ib $p |- ( ph -> ( ps -> ( ta -> th ) ) ) $=
      wph wps wch wth wta syl7ib.1 wta wch syl7ib.2 biimp syl7 $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl8ib.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl8ib.2 $e |- ( th <-> ta ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the consequent of the first premise. $)
    syl8ib $p |- ( ph -> ( ps -> ( ch -> ta ) ) ) $=
      wph wps wch wth wta syl8ib.1 wth wta syl8ib.2 biimp syl8 $.
      $( [1-Aug-1994] $)
  $}

  ${
    3imtr3.1 $e |- ( ph -> ps ) $.
    3imtr3.2 $e |- ( ph <-> ch ) $.
    3imtr3.3 $e |- ( ps <-> th ) $.
    $( A mixed syllogism inference, useful for removing a definition from both
       sides of an implication. $)
    3imtr3 $p |- ( ch -> th ) $=
      wch wps wth wch wph wps 3imtr3.2 3imtr3.1 sylbir 3imtr3.3 sylib $.
      $( [10-Aug-1994] $)
  $}

  ${
    3imtr4.1 $e |- ( ph -> ps ) $.
    3imtr4.2 $e |- ( ch <-> ph ) $.
    3imtr4.3 $e |- ( th <-> ps ) $.
    $( A mixed syllogism inference, useful for applying a definition to both
       sides of an implication. $)
    3imtr4 $p |- ( ch -> th ) $=
      wch wps wth wch wph wps 3imtr4.2 3imtr4.1 sylbi 3imtr4.3 sylibr $.
      $( [5-Aug-1993] $)
  $}

  ${
    con1bii.1 $e |- ( -. ph <-> ps ) $.
    $( A contraposition inference. $)
    con1bii $p |- ( -. ps <-> ph ) $=
      wps wn wph wph wps wph wn wps con1bii.1 biimp con1i wps wph wph wn wps
      con1bii.1 biimpr con2i impbi $.
      $( [5-Aug-1993] $)
  $}

  ${
    con2bii.1 $e |- ( ph <-> -. ps ) $.
    $( A contraposition inference. $)
    con2bii $p |- ( ps <-> -. ph ) $=
      wph wn wps wps wph wph wps wn con2bii.1 bicomi con1bii bicomi $.
      $( [5-Aug-1993] $)
  $}

  $( For ~ bicon3 :  See ~ negbii . $)

  $( For ~ con4bii :  Later. $)


$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Logical disjunction and conjunction
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

  $( Declare connectives for disjunction ('or') and conjunction ('and'). $)
  $c \/ $. $( Vee (read:  'or') $)
  $c /\ $. $( Wedge (read:  'and') $)

  $( Extend wff definition to include disjunction ('or'). $)
  wo $a wff ( ph \/ ps ) $.
  $( Extend wff definition to include conjunction ('and'). $)
  wa $a wff ( ph /\ ps ) $.

  $( Define disjunction (logical 'or').  This is our first use of the
     biconditional connective in a definition; we use it in place of the
     traditional "<=def=>", which means the same thing, except that we can
     manipulate the biconditional connective directly in proofs rather than
     having to rely on an informal definition substitution rule.  Note that
     if we mechanically substitute ` ( -. ph -> ps ) ` for ` ( ph \/ ps ) ` ,
     we end up with an instance of previously proved theorem ~ pm4.2 .  This
     is the justification for the definition, along with the fact that it
     introduces a new symbol ` \/ ` .  Definition of [Margaris] p. 49. $)
  df-or $a |- ( ( ph \/ ps ) <-> ( -. ph -> ps ) ) $.

  $( Define conjunction (logical 'and').  Definition of [Margaris] p. 49. $)
  df-an $a |- ( ( ph /\ ps ) <-> -. ( ph -> -. ps ) ) $.

  $( Theorem *4.64 of [WhiteheadRussell] p. 120. $)
  pm4.64 $p |-  ( ( -. ph -> ps ) <-> ( ph \/ ps ) ) $=
    wph wps wo wph wn wps wi wph wps df-or bicomi $.
    $( [1-Feb-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.54 of [WhiteheadRussell] p. 107. $)
  pm2.54 $p |-  ( ( -. ph -> ps ) -> ( ph \/ ps ) ) $=
    wph wps wo wph wn wps wi wph wps df-or biimpr $.
    $( [10-Feb-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.63 of [WhiteheadRussell] p. 120. $)
  pm4.63 $p |-  ( -. ( ph -> -. ps ) <-> ( ph /\ ps ) ) $=
    wph wps wa wph wps wn wi wn wph wps df-an bicomi $.
    $( [19-Feb-2005] $) $( [3-Jan-2005] $)

  $( Logical 'or' expressed in terms of implication only.  Theorem *5.25 of
     [WhiteheadRussell] p. 124. $)
  dfor2 $p |- ( ( ph \/ ps ) <-> ( ( ph -> ps ) -> ps ) ) $=
    wph wps wo wph wn wps wi wph wps wi wps wi wph wps df-or wph wn wps wi wph
    wps wi wps wi wph wps pm2.6 wph wn wph wps wi wps wph wps pm2.21 imim1i
    impbi bitr $.
    $( [20-Aug-2004] $) $( [12-Aug-2004] $)

  ${
    ori.1 $e |- ( ph \/ ps ) $.
    $( Infer implication from disjunction. $)
    ori $p |- ( -. ph -> ps ) $=
      wph wps wo wph wn wps wi ori.1 wph wps df-or mpbi $.
      $( [11-Jun-1994] $)
  $}

  ${
    orri.1 $e |- ( -. ph -> ps ) $.
    $( Infer implication from disjunction. $)
    orri $p |- ( ph \/ ps ) $=
      wph wps wo wph wn wps wi orri.1 wph wps df-or mpbir $.
      $( [11-Jun-1994] $)
  $}

  ${
    ord.1 $e |- ( ph -> ( ps \/ ch ) ) $.
    $( Deduce implication from disjunction. $)
    ord $p |- ( ph -> ( -. ps -> ch ) ) $=
      wph wps wch wo wps wn wch wi ord.1 wps wch df-or sylib $.
      $( [18-May-1994] $)
  $}

  ${
    orrd.1 $e |- ( ph -> ( -. ps -> ch ) ) $.
    $( Deduce implication from disjunction. $)
    orrd $p |- ( ph -> ( ps \/ ch ) ) $=
      wph wps wn wch wi wps wch wo orrd.1 wps wch df-or sylibr $.
      $( [27-Nov-1995] $)
  $}

  $( Implication in terms of disjunction.  Theorem *4.6 of
     [WhiteheadRussell] p. 120. $)
  imor $p |- ( ( ph -> ps ) <-> ( -. ph \/ ps ) ) $=
    wph wps wi wph wn wn wps wi wph wn wps wo wph wph wn wn wps wph pm4.13
    imbi1i wph wn wps df-or bitr4 $.
    $( [5-Aug-1993] $)

  $( Theorem *4.62 of [WhiteheadRussell] p. 120. $)
  pm4.62 $p |-  ( ( ph -> -. ps ) <-> ( -. ph \/ -. ps ) ) $=
    wph wps wn imor $.
    $( [24-Feb-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.66 of [WhiteheadRussell] p. 120. $)
  pm4.66 $p |-  ( ( -. ph -> -. ps ) <-> ( ph \/ -. ps ) ) $=
    wph wps wn pm4.64 $.
    $( [1-Feb-2005] $) $( [3-Jan-2005] $)

  $( Express implication in terms of conjunction.  Theorem 3.4(27) of [Stoll]
     p. 176. $)
  iman $p |- ( ( ph -> ps ) <-> -. ( ph /\ -. ps ) ) $=
    wph wps wi wph wps wn wn wi wph wps wn wa wn wps wps wn wn wph wps pm4.13
    imbi2i wph wps wn wa wph wps wn wn wi wph wps wn df-an con2bii bitr $.
    $( [5-Aug-1993] $)

  $( Express conjunction in terms of implication. $)
  annim $p |- ( ( ph /\ -. ps ) <-> -. ( ph -> ps ) ) $=
    wph wps wi wph wps wn wa wph wps iman con2bii $.
    $( [2-Aug-1994] $)

  $( Theorem *4.61 of [WhiteheadRussell] p. 120. $)
  pm4.61 $p |-  ( -. ( ph -> ps ) <-> ( ph /\ -. ps ) ) $=
    wph wps wn wa wph wps wi wn wph wps annim bicomi $.
    $( [24-Feb-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.65 of [WhiteheadRussell] p. 120. $)
  pm4.65 $p |-  ( -. ( -. ph -> ps ) <-> ( -. ph /\ -. ps ) ) $=
    wph wn wps pm4.61 $.
    $( [24-Feb-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.67 of [WhiteheadRussell] p. 120. $)
  pm4.67 $p |-  ( -. ( -. ph -> -. ps ) <-> ( -. ph /\ ps ) ) $=
    wph wn wps pm4.63 $.
    $( [27-Feb-2005] $) $( [3-Jan-2005] $)

  $( Express implication in terms of conjunction. $)
  imnan $p |- ( ( ph -> -. ps ) <-> -. ( ph /\ ps ) ) $=
    wph wps wa wph wps wn wi wph wps df-an con2bii $.
    $( [9-Apr-1994] $)

  $( Idempotent law for disjunction.  Theorem *4.25 of [WhiteheadRussell]
     p. 117. $)
  oridm $p |- ( ( ph \/ ph ) <-> ph ) $=
    wph wph wo wph wn wph wi wph wph wph df-or wph wph wn wph wi wph wph pm2.24
    wph pm2.18 impbi bitr4 $.
    $( [5-Aug-1993] $)

  $( Theorem *4.25 of [WhiteheadRussell] p. 117. $)
  pm4.25 $p |-  ( ph <-> ( ph \/ ph ) ) $=
    wph wph wo wph wph oridm bicomi $.
    $( [27-Feb-2005] $) $( [3-Jan-2005] $)

  $( Axiom *1.2 (Taut) of [WhiteheadRussell] p. 96. $)
  pm1.2 $p |-  ( ( ph \/ ph ) -> ph ) $=
    wph wph wo wph wph oridm biimp $.
    $( [27-Feb-2005] $) $( [3-Jan-2005] $)

  $( Commutative law for disjunction.  Theorem *4.31 of [WhiteheadRussell]
     p. 118. $)
  orcom $p |- ( ( ph \/ ps ) <-> ( ps \/ ph ) ) $=
    wph wn wps wi wps wn wph wi wph wps wo wps wph wo wph wps bi2.15 wph wps
    df-or wps wph df-or 3bitr4 $.
    $( [5-Aug-1993] $)

  $( Axiom *1.4 of [WhiteheadRussell] p. 96. $)
  pm1.4 $p |-  ( ( ph \/ ps ) -> ( ps \/ ph ) ) $=
    wph wps wo wps wph wo wph wps orcom biimp $.
    $( [27-Feb-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.62 of [WhiteheadRussell] p. 107. $)
  pm2.62 $p |-  ( ( ph \/ ps ) -> ( ( ph -> ps ) -> ps ) ) $=
    wph wps wo wph wps wi wps wi wph wps dfor2 biimp $.
    $( [6-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.621 of [WhiteheadRussell] p. 107. $)
  pm2.621 $p |-  ( ( ph -> ps ) -> ( ( ph \/ ps ) -> ps ) ) $=
    wph wps wo wph wps wi wps wph wps pm2.62 com12 $.
    $( [6-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.68 of [WhiteheadRussell] p. 108. $)
  pm2.68 $p |-  ( ( ( ph -> ps ) -> ps ) -> ( ph \/ ps ) ) $=
    wph wps wo wph wps wi wps wi wph wps dfor2 biimpr $.
    $( [27-Feb-2005] $) $( [3-Jan-2005] $)

  $( Elimination of disjunction by denial of a disjunct.  Theorem *2.55 of
     [WhiteheadRussell] p. 107. $)
  orel1 $p |- ( -. ph -> ( ( ph \/ ps ) -> ps ) ) $=
    wph wps wo wph wn wps wph wps wo wph wn wps wi wph wps df-or biimp com12 $.
    $( [12-Aug-1994] $)

  $( Elimination of disjunction by denial of a disjunct.  Theorem *2.56 of
     [WhiteheadRussell] p. 107. $)
  orel2 $p |- ( -. ph -> ( ( ps \/ ph ) -> ps ) ) $=
    wph wn wph wps wo wps wps wph wo wph wps orel1 wps wph orcom syl5ib $.
    $( [12-Aug-1994] $)

  $( Theorem *2.25 of [WhiteheadRussell] p. 104. $)
  pm2.25 $p |-  ( ph \/ ( ( ph \/ ps ) -> ps ) ) $=
    wph wph wps wo wps wi wph wps orel1 orri $.
    $( [1-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.53 of [WhiteheadRussell] p. 107. $)
  pm2.53 $p |-  ( ( ph \/ ps ) -> ( -. ph -> ps ) ) $=
    wph wn wph wps wo wps wph wps orel1 com12 $.
    $( [1-Mar-2005] $) $( [3-Jan-2005] $)

  ${
    orbi2i.1 $e |- ( ph <-> ps ) $.

    $( Inference adding a left disjunct to both sides of a logical
       equivalence. $)
    orbi2i $p |- ( ( ch \/ ph ) <-> ( ch \/ ps ) ) $=
      wch wn wph wi wch wn wps wi wch wph wo wch wps wo wph wps wch wn orbi2i.1
      imbi2i wch wph df-or wch wps df-or 3bitr4 $.
      $( [5-Aug-1993] $)

    $( Inference adding a right disjunct to both sides of a logical
       equivalence. $)
    orbi1i $p |- ( ( ph \/ ch ) <-> ( ps \/ ch ) ) $=
      wph wch wo wch wph wo wch wps wo wps wch wo wph wch orcom wph wps wch
      orbi2i.1 orbi2i wch wps orcom 3bitr $.
      $( [5-Aug-1993] $)

  $}

  ${
    orbi12i.1 $e |- ( ph <-> ps ) $.
    orbi12i.2 $e |- ( ch <-> th ) $.
    $( Infer the disjunction of two equivalences. $)
    orbi12i $p |- ( ( ph \/ ch ) <-> ( ps \/ th ) ) $=
      wph wch wo wph wth wo wps wth wo wch wth wph orbi12i.2 orbi2i wph wps wth
      orbi12i.1 orbi1i bitr $.
      $( [5-Aug-1993] $)
  $}

  $( A rearrangement of disjuncts. $)
  or12 $p |- ( ( ph \/ ( ps \/ ch ) ) <-> ( ps \/ ( ph \/ ch ) ) ) $=
    wph wn wps wch wo wi wps wn wph wch wo wi wph wps wch wo wo wps wph wch wo
    wo wps wn wph wn wch wi wi wph wn wps wn wch wi wi wps wn wph wch wo wi wph
    wn wps wch wo wi wps wn wph wn wch bi2.04 wph wch wo wph wn wch wi wps wn
    wph wch df-or imbi2i wps wch wo wps wn wch wi wph wn wps wch df-or imbi2i
    3bitr4r wph wps wch wo df-or wps wph wch wo df-or 3bitr4 $.
    $( [5-Aug-1993] $)

  $( Axiom *1.5 (Assoc) of [WhiteheadRussell] p. 96. $)
  pm1.5 $p |-  ( ( ph \/ ( ps \/ ch ) ) -> ( ps \/ ( ph \/ ch ) ) ) $=
    wph wps wch wo wo wps wph wch wo wo wph wps wch or12 biimp $.
    $( [1-Mar-2005] $) $( [3-Jan-2005] $)

  $( Associative law for disjunction.  Theorem *4.33 of [WhiteheadRussell]
     p. 118. $)
  orass $p |- ( ( ( ph \/ ps ) \/ ch ) <-> ( ph \/ ( ps \/ ch ) ) ) $=
    wch wph wps wo wo wph wch wps wo wo wph wps wo wch wo wph wps wch wo wo wch
    wph wps or12 wph wps wo wch orcom wps wch wo wch wps wo wph wps wch orcom
    orbi2i 3bitr4 $.
    $( [5-Aug-1993] $)

  $( Theorem *2.31 of [WhiteheadRussell] p. 104. $)
  pm2.31 $p |-  ( ( ph \/ ( ps \/ ch ) ) -> ( ( ph \/ ps ) \/ ch ) ) $=
    wph wps wo wch wo wph wps wch wo wo wph wps wch orass biimpr $.
    $( [2-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.32 of [WhiteheadRussell] p. 105. $)
  pm2.32 $p |-  ( ( ( ph \/ ps ) \/ ch ) -> ( ph \/ ( ps \/ ch ) ) ) $=
    wph wps wo wch wo wph wps wch wo wo wph wps wch orass biimp $.
    $( [6-Mar-2005] $) $( [3-Jan-2005] $)

  $( A rearrangement of disjuncts. $)
  or23 $p |- ( ( ( ph \/ ps ) \/ ch ) <-> ( ( ph \/ ch ) \/ ps ) ) $=
    wph wps wch wo wo wph wch wps wo wo wph wps wo wch wo wph wch wo wps wo wps
    wch wo wch wps wo wph wps wch orcom orbi2i wph wps wch orass wph wch wps
    orass 3bitr4 $.
    $( [18-Oct-1995] $)

  $( Rearrangement of 4 disjuncts. $)
  or4 $p |- ( ( ( ph \/ ps ) \/ ( ch \/ th ) ) <->
                ( ( ph \/ ch ) \/ ( ps \/ th ) ) ) $=
    wph wps wch wth wo wo wo wph wch wps wth wo wo wo wph wps wo wch wth wo wo
    wph wch wo wps wth wo wo wps wch wth wo wo wch wps wth wo wo wph wps wch
    wth or12 orbi2i wph wps wch wth wo orass wph wch wps wth wo orass 3bitr4 $.
    $( [12-Aug-1994] $)

  $( Rearrangement of 4 disjuncts. $)
  or42 $p |- ( ( ( ph \/ ps ) \/ ( ch \/ th ) ) <->
                 ( ( ph \/ ch ) \/ ( th \/ ps ) ) ) $=
    wph wps wo wch wth wo wo wph wch wo wps wth wo wo wph wch wo wth wps wo wo
    wph wps wch wth or4 wps wth wo wth wps wo wph wch wo wps wth orcom orbi2i
    bitr $.
    $( [11-Jan-2005] $) $( [10-Jan-2005] $)

  $( Distribution of disjunction over disjunction. $)
  orordi $p |- ( ( ph \/ ( ps \/ ch ) ) <->
               ( ( ph \/ ps ) \/ ( ph \/ ch ) ) ) $=
    wph wps wch wo wo wph wph wo wps wch wo wo wph wps wo wph wch wo wo wph wph
    wo wph wps wch wo wph oridm orbi1i wph wph wps wch or4 bitr3 $.
    $( [25-Feb-1995] $)

  $( Distribution of disjunction over disjunction. $)
  orordir $p |- ( ( ( ph \/ ps ) \/ ch ) <->
               ( ( ph \/ ch ) \/ ( ps \/ ch ) ) ) $=
    wph wps wo wch wo wph wps wo wch wch wo wo wph wch wo wps wch wo wo wch wch
    wo wch wph wps wo wch oridm orbi2i wph wps wch wch or4 bitr3 $.
    $( [25-Feb-1995] $)

  $( Introduction of a disjunct.  Axiom *1.3 of [WhiteheadRussell] p. 96. $)
  olc $p |- ( ph -> ( ps \/ ph ) ) $=
    wph wps wph wph wps wn ax-1 orrd $.
    $( [30-Aug-1993] $)

  $( Introduction of a disjunct.  Theorem *2.2 of [WhiteheadRussell] p. 104. $)
  orc $p |- ( ph -> ( ph \/ ps ) ) $=
    wph wph wps wph wps pm2.24 orrd $.
    $( [30-Aug-1993] $)

  ${
    orci.1 $e |- ph $.
    $( Deduction introducing a disjunct. $)
    orci $p |- ( ph \/ ps ) $=
      wph wph wps wo orci.1 wph wps orc ax-mp $.
      $( [20-Jan-2008] $) $( [19-Jan-2008] $)

    $( Deduction introducing a disjunct. $)
    olci $p |- ( ps \/ ph ) $=
      wph wps wph wo orci.1 wph wps olc ax-mp $.
      $( [20-Jan-2008] $) $( [19-Jan-2008] $)
  $}

  ${
    orcd.1 $e |- ( ph -> ps ) $.
    $( MAY BE REVISED - use the 2 theorems below to shorten others $)
    $( Deduction introducing a disjunct. $)
    orcd $p |- ( ph -> ( ps \/ ch ) ) $=
      wph wps wps wch wo orcd.1 wps wch orc syl $.
      $( [19-Feb-2008] $)

  $}

  ${
    orcs.1 $e |- ( ( ph \/ ps ) -> ch ) $.
    $( Deduction eliminating disjunct. $)
    orcs $p |- ( ph -> ch ) $=
      wph wph wps wo wch wph wps orc orcs.1 syl $.
      $( [21-Jun-1994] $)
  $}

  ${
    olcs.1 $e |- ( ( ph \/ ps ) -> ch ) $.
    $( Deduction eliminating disjunct. $)
    olcs $p |- ( ps -> ch ) $=
      wps wph wps wo wch wps wph olc olcs.1 syl $.
      $( [21-Jun-1994] $)
  $}

  $( Theorem *2.07 of [WhiteheadRussell] p. 101. $)
  pm2.07 $p |-  ( ph -> ( ph \/ ph ) ) $=
    wph wph olc $.
    $( [6-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.45 of [WhiteheadRussell] p. 106. $)
  pm2.45 $p |-  ( -. ( ph \/ ps ) -> -. ph ) $=
    wph wph wps wo wph wps orc con3i $.
    $( [8-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.46 of [WhiteheadRussell] p. 106. $)
  pm2.46 $p |-  ( -. ( ph \/ ps ) -> -. ps ) $=
    wps wph wps wo wps wph olc con3i $.
    $( [8-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.47 of [WhiteheadRussell] p. 107. $)
  pm2.47 $p |-  ( -. ( ph \/ ps ) -> ( -. ph \/ ps ) ) $=
    wph wps wo wn wph wn wph wn wps wo wph wps pm2.45 wph wn wps orc syl $.
    $( [6-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.48 of [WhiteheadRussell] p. 107. $)
  pm2.48 $p |-  ( -. ( ph \/ ps ) -> ( ph \/ -. ps ) ) $=
    wph wps wo wn wph wps wn wph wps wo wn wps wn wph wn wph wps pm2.46 a1d
    orrd $.
    $( [9-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.49 of [WhiteheadRussell] p. 107. $)
  pm2.49 $p |-  ( -. ( ph \/ ps ) -> ( -. ph \/ -. ps ) ) $=
    wph wps wo wn wph wn wps wn wph wps wo wn wps wn wph wn wn wph wps pm2.46
    a1d orrd $.
    $( [7-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.67 of [WhiteheadRussell] p. 107. $)
  pm2.67 $p |-  ( ( ( ph \/ ps ) -> ps ) -> ( ph -> ps ) ) $=
    wph wph wps wo wps wph wps orc imim1i $.
    $( [6-Jan-2005] $) $( [3-Jan-2005] $)

  $( Join antecedents with conjunction.  Theorem *3.2 of [WhiteheadRussell]
     p. 111. $)
  pm3.2 $p |- ( ph -> ( ps -> ( ph /\ ps ) ) ) $=
    wph wps wph wps wa wph wps wa wph wps wn wi wn wph wps df-an biimpr expi $.
    $( [5-Aug-1993] $)

  $( Join antecedents with conjunction.  Theorem *3.21 of
     [WhiteheadRussell] p. 111. $)
  pm3.21 $p |- ( ph -> ( ps -> ( ps /\ ph ) ) ) $=
    wps wph wps wph wa wps wph pm3.2 com12 $.
    $( [5-Aug-1993] $)

  ${
    pm3.2i.1 $e |- ph $.
    pm3.2i.2 $e |- ps $.
    $( Infer conjunction of premises. $)
    pm3.2i $p |- ( ph /\ ps ) $=
      wph wps wph wps wa pm3.2i.1 pm3.2i.2 wph wps pm3.2 mp2 $.
      $( [5-Aug-1993] $)
  $}

  $( Theorem *3.37 (Transp) of [WhiteheadRussell] p. 112. $)
  pm3.37 $p |-  ( ( ( ph /\ ps ) -> ch ) -> ( ( ph /\ -. ch ) -> -. ps ) ) $=
    wph wps wa wch wi wps wph wch wn wa wph wps wa wch wi wps wph wch wi wph
    wch wn wa wn wps wph wps wa wch wi wph wch wi wps wph wph wps wa wch wps
    wph pm3.21 imim1d com12 wph wch iman syl6ib con2d $.
    $( [7-Mar-2005] $) $( [3-Jan-2005] $)

  $( Nested conjunction of antecedents. $)
  pm3.43i $p |- ( ( ph -> ps ) ->
                ( ( ph -> ch ) -> ( ph -> ( ps /\ ch ) ) ) ) $=
    wps wch wps wch wa wph wps wch pm3.2 imim3i $.
    $( [5-Aug-1993] $)

  ${
    jca.1 $e |- ( ph -> ps ) $.
    jca.2 $e |- ( ph -> ch ) $.
    $( Deduce conjunction of the consequents of two implications ("join
       consequents with 'and'"). $)
    jca $p |- ( ph -> ( ps /\ ch ) ) $=
      wph wps wch wn wi wn wps wch wa wph wps wch jca.1 jca.2 jc wps wch df-an
      sylibr $.
      $( [5-Aug-1993] $)
  $}

  ${
    jcai.1 $e |- ( ph -> ps ) $.
    jcai.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction replacing implication with conjunction. $)
    jcai $p |- ( ph -> ( ps /\ ch ) ) $=
      wph wps wch jcai.1 wph wps wch jcai.1 jcai.2 mpd jca $.
      $( [5-Aug-1993] $)
  $}

  ${
    jctl.1 $e |- ps $.
    $( Inference conjoining a theorem to the left of a consequent. $)
    jctl $p |- ( ph -> ( ps /\ ph ) ) $=
      wph wps wph wps wph jctl.1 a1i wph id jca $.
      $( [31-Dec-1993] $)
  $}

  ${
    jctr.1 $e |- ps $.
    $( Inference conjoining a theorem to the right of a consequent. $)
    jctr $p |- ( ph -> ( ph /\ ps ) ) $=
      wph wph wps wph id wps wph jctr.1 a1i jca $.
      $( [18-Aug-1993] $)
  $}

  ${
    jctil.1 $e |- ( ph -> ps ) $.
    jctil.2 $e |- ch $.
    $( Inference conjoining a theorem to left of consequent in an
       implication. $)
    jctil $p |- ( ph -> ( ch /\ ps ) ) $=
      wph wch wps wch wph jctil.2 a1i jctil.1 jca $.
      $( [31-Dec-1993] $)
  $}

  ${
    jctir.1 $e |- ( ph -> ps ) $.
    jctir.2 $e |- ch $.
    $( Inference conjoining a theorem to right of consequent in an
       implication. $)
    jctir $p |- ( ph -> ( ps /\ ch ) ) $=
      wph wps wch jctir.1 wch wph jctir.2 a1i jca $.
      $( [31-Dec-1993] $)
  $}

  $( Conjoin antecedent to left of consequent. $)
  ancl $p |- ( ( ph -> ps ) -> ( ph -> ( ph /\ ps ) ) ) $=
    wph wps wph wps wa wph wps pm3.2 a2i $.
    $( [15-Aug-1994] $)

  $( Conjoin antecedent to right of consequent. $)
  ancr $p |- ( ( ph -> ps ) -> ( ph -> ( ps /\ ph ) ) ) $=
    wph wps wps wph wa wph wps pm3.21 a2i $.
    $( [15-Aug-1994] $)

  ${
    ancli.1 $e |- ( ph -> ps ) $.
    $( Deduction conjoining antecedent to left of consequent. $)
    ancli $p |- ( ph -> ( ph /\ ps ) ) $=
      wph wph wps wph id ancli.1 jca $.
      $( [12-Aug-1993] $)
  $}

  ${
    ancri.1 $e |- ( ph -> ps ) $.
    $( Deduction conjoining antecedent to right of consequent. $)
    ancri $p |- ( ph -> ( ps /\ ph ) ) $=
      wph wps wph ancri.1 wph id jca $.
      $( [15-Aug-1994] $)
  $}

  ${
    ancld.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction conjoining antecedent to left of consequent in nested
       implication. $)
    ancld $p |- ( ph -> ( ps -> ( ps /\ ch ) ) ) $=
      wph wps wch wi wps wps wch wa wi ancld.1 wps wch ancl syl $.
      $( [15-Aug-1994] $)
  $}

  ${
    ancrd.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction conjoining antecedent to right of consequent in nested
       implication. $)
    ancrd $p |- ( ph -> ( ps -> ( ch /\ ps ) ) ) $=
      wph wps wch wi wps wch wps wa wi ancrd.1 wps wch ancr syl $.
      $( [15-Aug-1994] $)
  $}

  $( Conjoin antecedent to left of consequent in nested implication. $)
  anc2l $p |- ( ( ph -> ( ps -> ch ) ) -> ( ph -> ( ps -> ( ph /\ ch ) ) ) ) $=
    wph wps wch wi wps wph wch wa wi wph wch wph wch wa wps wph wch pm3.2
    imim2d a2i $.
    $( [10-Aug-1994] $)

  $( Conjoin antecedent to right of consequent in nested implication. $)
  anc2r $p |- ( ( ph -> ( ps -> ch ) ) -> ( ph -> ( ps -> ( ch /\ ph ) ) ) ) $=
    wph wps wch wi wps wch wph wa wi wph wch wch wph wa wps wph wch pm3.21
    imim2d a2i $.
    $( [15-Aug-1994] $)

  ${
    anc2li.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction conjoining antecedent to left of consequent in nested
       implication. $)
    anc2li $p |- ( ph -> ( ps -> ( ph /\ ch ) ) ) $=
      wph wps wch wi wi wph wps wph wch wa wi wi anc2li.1 wph wps wch anc2l
      ax-mp $.
      $( [10-Aug-1994] $)
  $}

  ${
    anc2ri.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction conjoining antecedent to right of consequent in nested
       implication. $)
    anc2ri $p |- ( ph -> ( ps -> ( ch /\ ph ) ) ) $=
      wph wps wch wi wi wph wps wch wph wa wi wi anc2ri.1 wph wps wch anc2r
      ax-mp $.
      $( [15-Aug-1994] $)
  $}

  $( Conjunction in terms of disjunction (DeMorgan's law).  Theorem *4.5 of
     [WhiteheadRussell] p. 120. $)
  anor $p |- ( ( ph /\ ps ) <-> -. ( -. ph \/ -. ps ) ) $=
    wph wps wa wph wps wn wi wn wph wn wps wn wo wn wph wps df-an wph wps wn wi
    wph wn wps wn wo wph wps pm4.62 negbii bitr $.
    $( [5-Aug-1993] $)

  $( Negated conjunction in terms of disjunction (DeMorgan's law).  Theorem
     *4.51 of [WhiteheadRussell] p. 120. $)
  ianor $p |- ( -. ( ph /\ ps ) <-> ( -. ph \/ -. ps ) ) $=
    wph wps wa wn wph wn wps wn wo wn wn wph wn wps wn wo wph wps wa wph wn wps
    wn wo wn wph wps anor negbii wph wn wps wn wo pm4.13 bitr4 $.
    $( [5-Aug-1993] $)

  $( Negated disjunction in terms of conjunction (DeMorgan's law).  Compare
     Theorem *4.56 of [WhiteheadRussell] p. 120. $)
  ioran $p |- ( -. ( ph \/ ps ) <-> ( -. ph /\ -. ps ) ) $=
    wph wps wo wn wph wn wn wps wn wn wo wn wph wn wps wn wa wph wps wo wph wn
    wn wps wn wn wo wph wph wn wn wps wps wn wn wph pm4.13 wps pm4.13 orbi12i
    negbii wph wn wps wn anor bitr4 $.
    $( [5-Aug-1993] $)

  $( Theorem *4.52 of [WhiteheadRussell] p. 120. $)
  pm4.52 $p |-  ( ( ph /\ -. ps ) <-> -. ( -. ph \/ ps ) ) $=
    wph wps wn wa wph wn wps wn wn wo wn wph wn wps wo wn wph wps wn anor wph
    wn wps wo wph wn wps wn wn wo wps wps wn wn wph wn wps pm4.13 orbi2i negbii
    bitr4 $.
    $( [11-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.53 of [WhiteheadRussell] p. 120. $)
  pm4.53 $p |-  ( -. ( ph /\ -. ps ) <-> ( -. ph \/ ps ) ) $=
    wph wn wps wo wph wps wn wa wn wph wps wn wa wph wn wps wo wph wps pm4.52
    con2bii bicomi $.
    $( [11-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.54 of [WhiteheadRussell] p. 120. $)
  pm4.54 $p |-  ( ( -. ph /\ ps ) <-> -. ( ph \/ -. ps ) ) $=
    wph wn wps wa wph wn wn wps wn wo wn wph wps wn wo wn wph wn wps anor wph
    wps wn wo wph wn wn wps wn wo wph wph wn wn wps wn wph pm4.13 orbi1i negbii
    bitr4 $.
    $( [11-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.55 of [WhiteheadRussell] p. 120. $)
  pm4.55 $p |-  ( -. ( -. ph /\ ps ) <-> ( ph \/ -. ps ) ) $=
    wph wps wn wo wph wn wps wa wn wph wn wps wa wph wps wn wo wph wps pm4.54
    con2bii bicomi $.
    $( [11-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.56 of [WhiteheadRussell] p. 120. $)
  pm4.56 $p |-  ( ( -. ph /\ -. ps ) <-> -. ( ph \/ ps ) ) $=
    wph wps wo wn wph wn wps wn wa wph wps ioran bicomi $.
    $( [11-Mar-2005] $) $( [3-Jan-2005] $)

  $( Disjunction in terms of conjunction (DeMorgan's law).  Compare Theorem
     *4.57 of [WhiteheadRussell] p. 120. $)
  oran $p |- ( ( ph \/ ps ) <-> -. ( -. ph /\ -. ps ) ) $=
    wph wps wo wph wps wo wn wn wph wn wps wn wa wn wph wps wo pm4.13 wph wps
    wo wn wph wn wps wn wa wph wps ioran negbii bitr $.
    $( [5-Aug-1993] $)

  $( Theorem *4.57 of [WhiteheadRussell] p. 120. $)
  pm4.57 $p |-  ( -. ( -. ph /\ -. ps ) <-> ( ph \/ ps ) ) $=
    wph wps wo wph wn wps wn wa wn wph wps oran bicomi $.
    $( [11-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *3.1 of [WhiteheadRussell] p. 111. $)
  pm3.1 $p |-  ( ( ph /\ ps ) -> -. ( -. ph \/ -. ps ) ) $=
    wph wps wa wph wn wps wn wo wn wph wps anor biimp $.
    $( [21-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *3.11 of [WhiteheadRussell] p. 111. $)
  pm3.11 $p |-  ( -. ( -. ph \/ -. ps ) -> ( ph /\ ps ) ) $=
    wph wps wa wph wn wps wn wo wn wph wps anor biimpr $.
    $( [25-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *3.12 of [WhiteheadRussell] p. 111. $)
  pm3.12 $p |-  ( ( -. ph \/ -. ps ) \/ ( ph /\ ps ) ) $=
    wph wn wps wn wo wph wps wa wph wps pm3.11 orri $.
    $( [25-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *3.13 of [WhiteheadRussell] p. 111. $)
  pm3.13 $p |-  ( -. ( ph /\ ps ) -> ( -. ph \/ -. ps ) ) $=
    wph wn wps wn wo wph wps wa wph wps pm3.11 con1i $.
    $( [25-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *3.14 of [WhiteheadRussell] p. 111. $)
  pm3.14 $p |-  ( ( -. ph \/ -. ps ) -> -. ( ph /\ ps ) ) $=
    wph wps wa wph wn wps wn wo wph wps pm3.1 con2i $.
    $( [25-Mar-2005] $) $( [3-Jan-2005] $)

  $( Elimination of a conjunct.  Theorem *3.26 (Simp) of [WhiteheadRussell]
     p. 112. $)
  pm3.26 $p |- ( ( ph /\ ps ) -> ph ) $=
    wph wps wa wph wps wn wi wn wph wph wps df-an wph wps pm3.26im sylbi $.
    $( [5-Aug-1993] $)

  ${
    pm3.26i.1 $e |- ( ph /\ ps ) $.
    $( Inference eliminating a conjunct. $)
    pm3.26i $p |- ph $=
      wph wps wa wph pm3.26i.1 wph wps pm3.26 ax-mp $.
      $( [15-Jun-1994] $)
  $}

  ${
    pm3.26d.1 $e |- ( ph -> ( ps /\ ch ) ) $.
    $( Deduction eliminating a conjunct. $)
    pm3.26d $p |- ( ph -> ps ) $=
      wph wps wch wa wps pm3.26d.1 wps wch pm3.26 syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    pm3.26bi.1 $e |- ( ph <-> ( ps /\ ch ) ) $.
    $( Deduction eliminating a conjunct. $)
    pm3.26bi $p |- ( ph -> ps ) $=
      wph wps wch wph wps wch wa pm3.26bi.1 biimp pm3.26d $.
      $( [27-May-1998] $)
  $}

  $( Elimination of a conjunct.  Theorem *3.27 (Simp) of [WhiteheadRussell]
     p. 112. $)
  pm3.27 $p |- ( ( ph /\ ps ) -> ps ) $=
    wph wps wa wph wps wn wi wn wps wph wps df-an wph wps pm3.27im sylbi $.
    $( [5-Aug-1993] $)

  ${
    pm3.27i.1 $e |- ( ph /\ ps ) $.
    $( Inference eliminating a conjunct. $)
    pm3.27i $p |- ps $=
      wph wps wa wps pm3.27i.1 wph wps pm3.27 ax-mp $.
      $( [15-Jun-1994] $)
  $}

  ${
    pm3.27d.1 $e |- ( ph -> ( ps /\ ch ) ) $.
    $( Deduction eliminating a conjunct. $)
    pm3.27d $p |- ( ph -> ch ) $=
      wph wps wch wa wch pm3.27d.1 wps wch pm3.27 syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    pm3.27bi.1 $e |- ( ph <-> ( ps /\ ch ) ) $.
    $( Deduction eliminating a conjunct. $)
    pm3.27bi $p |- ( ph -> ch ) $=
      wph wps wch wph wps wch wa pm3.27bi.1 biimp pm3.27d $.
      $( [27-May-1998] $)
  $}

  $( Theorem *3.41 of [WhiteheadRussell] p. 113. $)
  pm3.41 $p |-  ( ( ph -> ch ) -> ( ( ph /\ ps ) -> ch ) ) $=
    wph wps wa wph wch wph wps pm3.26 imim1i $.
    $( [21-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *3.42 of [WhiteheadRussell] p. 113. $)
  pm3.42 $p |-  ( ( ps -> ch ) -> ( ( ph /\ ps ) -> ch ) ) $=
    wph wps wa wps wch wph wps pm3.27 imim1i $.
    $( [27-Mar-2005] $) $( [3-Jan-2005] $)

  $( Conjoin antecedent to left of consequent.  Theorem *4.7 of
     [WhiteheadRussell] p. 120. $)
  anclb $p |- ( ( ph -> ps ) <-> ( ph -> ( ph /\ ps ) ) ) $=
    wph wps wi wph wph wps wa wi wph wps ancl wph wps wa wps wph wph wps pm3.27
    imim2i impbi $.
    $( [25-Jul-1999] $)

  $( Conjoin antecedent to right of consequent. $)
  ancrb $p |- ( ( ph -> ps ) <-> ( ph -> ( ps /\ ph ) ) ) $=
    wph wps wi wph wps wph wa wi wph wps ancr wps wph wa wps wph wps wph pm3.26
    imim2i impbi $.
    $( [25-Jul-1999] $)

  $( Conjunction implies implication.  Theorem *3.4 of [WhiteheadRussell]
     p. 113. $)
  pm3.4 $p |- ( ( ph /\ ps ) -> ( ph -> ps ) ) $=
    wph wps wa wps wph wph wps pm3.27 a1d $.
    $( [31-Jul-1995] $)

  $( Conjunction with implication.  Compare Theorem *4.45 of
     [WhiteheadRussell] p. 119. $)
  pm4.45im $p |- ( ph <-> ( ph /\ ( ps -> ph ) ) ) $=
    wph wph wps wph wi wa wph wps wph wi wph wps ax-1 ancli wph wps wph wi
    pm3.26 impbi $.
    $( [17-May-1998] $)

  ${
    anim12i.1 $e |- ( ph -> ps ) $.
    anim12i.2 $e |- ( ch -> th ) $.
    $( Conjoin antecedents and consequents of two premises. $)
    anim12i $p |- ( ( ph /\ ch ) -> ( ps /\ th ) ) $=
      wph wch wa wps wth wph wch wa wph wps wph wch pm3.26 anim12i.1 syl wph
      wch wa wch wth wph wch pm3.27 anim12i.2 syl jca $.
      $( [5-Aug-1993] $)
  $}

  ${
    anim1i.1 $e |- ( ph -> ps ) $.
    $( Introduce conjunct to both sides of an implication. $)
    anim1i $p |- ( ( ph /\ ch ) -> ( ps /\ ch ) ) $=
      wph wps wch wch anim1i.1 wch id anim12i $.
      $( [5-Aug-1993] $)

    $( Introduce conjunct to both sides of an implication. $)
    anim2i $p |- ( ( ch /\ ph ) -> ( ch /\ ps ) ) $=
      wch wch wph wps wch id anim1i.1 anim12i $.
      $( [5-Aug-1993] $)
  $}

  ${
    orim12i.1 $e |- ( ph -> ps ) $.
    orim12i.2 $e |- ( ch -> th ) $.
    $( Disjoin antecedents and consequents of two premises. $)
    orim12i $p |- ( ( ph \/ ch ) -> ( ps \/ th ) ) $=
      wph wn wch wn wa wn wps wn wth wn wa wn wph wch wo wps wth wo wps wn wth
      wn wa wph wn wch wn wa wps wn wph wn wth wn wch wn wph wps orim12i.1
      con3i wch wth orim12i.2 con3i anim12i con3i wph wch oran wps wth oran
      3imtr4 $.
      $( [6-Jun-1994] $)
  $}

  ${
    orim1i.1 $e |- ( ph -> ps ) $.
    $( Introduce disjunct to both sides of an implication. $)
    orim1i $p |- ( ( ph \/ ch ) -> ( ps \/ ch ) ) $=
      wph wps wch wch orim1i.1 wch id orim12i $.
      $( [6-Jun-1994] $)

    $( Introduce disjunct to both sides of an implication. $)
    orim2i $p |- ( ( ch \/ ph ) -> ( ch \/ ps ) ) $=
      wch wch wph wps wch id orim1i.1 orim12i $.
      $( [6-Jun-1994] $)
  $}

  $( Theorem *2.3 of [WhiteheadRussell] p. 104. $)
  pm2.3 $p |-  ( ( ph \/ ( ps \/ ch ) ) -> ( ph \/ ( ch \/ ps ) ) ) $=
    wps wch wo wch wps wo wph wps wch pm1.4 orim2i $.
    $( [2-Apr-2005] $) $( [3-Jan-2005] $)

  $( Disjunction of antecedents.  Compare Theorem *3.44 of
     [WhiteheadRussell] p. 113. $)
  jao $p |- ( ( ph -> ps ) -> ( ( ch -> ps ) -> ( ( ph \/ ch ) -> ps ) ) ) $=
    wph wps wi wps wn wph wn wi wch wps wi wph wch wo wps wi wi wph wps con3
    wps wn wph wn wi wps wn wch wn wi wph wch wo wps wi wch wps wi wps wn wph
    wn wi wps wn wch wn wi wph wn wch wn wa wn wps wph wch wo wps wn wph wn wi
    wps wn wch wn wi wps wn wph wn wch wn wa wi wph wn wch wn wa wn wps wi wps
    wn wph wn wch wn pm3.43i wps wph wn wch wn wa con1 syl6 wph wch oran syl7ib
    wch wps con3 syl5 syl $.
    $( [5-Apr-1994] $)

  ${
    jaoi.1 $e |- ( ph -> ps ) $.
    jaoi.2 $e |- ( ch -> ps ) $.
    $( Inference disjoining the antecedents of two implications. $)
    jaoi $p |- ( ( ph \/ ch ) -> ps ) $=
      wph wps wi wch wps wi wph wch wo wps wi jaoi.1 jaoi.2 wph wps wch jao mp2
      $.
      $( [5-Apr-1994] $)
  $}

  $( Theorem *2.41 of [WhiteheadRussell] p. 106. $)
  pm2.41 $p |-  ( ( ps \/ ( ph \/ ps ) ) -> ( ph \/ ps ) ) $=
    wps wph wps wo wph wps wo wps wph olc wph wps wo id jaoi $.
    $( [2-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.42 of [WhiteheadRussell] p. 106. $)
  pm2.42 $p |-  ( ( -. ph \/ ( ph -> ps ) ) -> ( ph -> ps ) ) $=
    wph wn wph wps wi wph wps wi wph wps pm2.21 wph wps wi id jaoi $.
    $( [2-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.4 of [WhiteheadRussell] p. 106. $)
  pm2.4 $p |-  ( ( ph \/ ( ph \/ ps ) ) -> ( ph \/ ps ) ) $=
    wph wph wps wo wph wps wo wph wps orc wph wps wo id jaoi $.
    $( [2-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.44 of [WhiteheadRussell] p. 119. $)
  pm4.44 $p |-  ( ph <-> ( ph \/ ( ph /\ ps ) ) ) $=
    wph wph wph wps wa wo wph wph wps wa orc wph wph wph wps wa wph id wph wps
    pm3.26 jaoi impbi $.
    $( [2-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.63 of [WhiteheadRussell] p. 125. $)
  pm5.63 $p |-  ( ( ph \/ ps ) <-> ( ph \/ ( -. ph /\ ps ) ) ) $=
    wph wps wo wph wph wn wps wa wo wph wps wo wph wph wn wps wa wph wps wo wph
    wn wps wph wps pm2.53 ancld orrd wph wph wn wps wa wo wph wps wph wph wn
    wps wi wph wn wps wa wph wps pm2.24 wph wn wps pm3.4 jaoi orrd impbi $.
    $( [2-Apr-2005] $) $( [3-Jan-2005] $)

  $( Import-export theorem.  Part of Theorem *4.87 of [WhiteheadRussell]
     p. 122. $)
  impexp $p |- ( ( ( ph /\ ps ) -> ch ) <-> ( ph -> ( ps -> ch ) ) ) $=
    wph wps wa wch wi wph wps wn wi wn wch wi wph wps wch wi wi wph wps wa wph
    wps wn wi wn wch wph wps df-an imbi1i wph wps wn wi wn wch wi wph wps wch
    wi wi wph wps wch expt wph wps wch impt impbi bitr $.
    $( [5-Aug-1993] $)

  $( Theorem *3.3 (Exp) of [WhiteheadRussell] p. 112. $)
  pm3.3 $p |-  ( ( ( ph /\ ps ) -> ch ) -> ( ph -> ( ps -> ch ) ) ) $=
    wph wps wa wch wi wph wps wch wi wi wph wps wch impexp biimp $.
    $( [10-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *3.31 (Imp) of [WhiteheadRussell] p. 112. $)
  pm3.31 $p |-  ( ( ph -> ( ps -> ch ) ) -> ( ( ph /\ ps ) -> ch ) ) $=
    wph wps wa wch wi wph wps wch wi wi wph wps wch impexp biimpr $.
    $( [14-Apr-2005] $) $( [3-Jan-2005] $)

  ${
    imp.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Importation inference.  (The proof was shortened by Eric Schmidt,
       22-Dec-2006.) $)
    imp $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wa wch wi wph wps wch wi wi imp.1 wph wps wch impexp mpbir $.
      $( [22-Dec-2006] $) $( [5-Aug-1993] $)

    $( Importation inference with commuted antecedents. $)
    impcom $p |- ( ( ps /\ ph ) -> ch ) $=
      wps wph wch wph wps wch imp.1 com12 imp $.
      $( [26-May-2005] $) $( [25-May-2005] $)
  $}

  $( Theorem *4.14 of [WhiteheadRussell] p. 117. $)
  pm4.14 $p |-  ( ( ( ph /\ ps ) -> ch ) <-> ( ( ph /\ -. ch ) -> -. ps ) ) $=
    wph wps wa wch wi wps wph wch wi wi wps wph wch wn wa wn wi wph wch wn wa
    wps wn wi wph wps wa wch wi wph wps wch wi wi wps wph wch wi wi wph wps wch
    impexp wph wps wch bi2.04 bitr wph wch wi wph wch wn wa wn wps wph wch iman
    imbi2i wps wph wch wn wa bi2.03 3bitr $.
    $( [11-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.15 of [WhiteheadRussell] p. 117. $)
  pm4.15 $p |-  ( ( ( ph /\ ps ) -> -. ch ) <-> ( ( ps /\ ch ) -> -. ph ) ) $=
    wph wps wa wch wn wi wph wps wch wn wi wi wph wps wch wa wn wi wps wch wa
    wph wn wi wph wps wch wn impexp wps wch wn wi wps wch wa wn wph wps wch
    imnan imbi2i wph wps wch wa bi2.03 3bitr $.
    $( [11-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.78 of [WhiteheadRussell] p. 121. $)
  pm4.78 $p |-  ( ( ( ph -> ps ) \/ ( ph -> ch ) ) <->
                ( ph -> ( ps \/ ch ) ) ) $=
    wph wps wi wn wph wch wi wi wph wps wn wch wi wi wph wps wi wph wch wi wo
    wph wps wch wo wi wph wps wn wa wph wch wi wi wph wps wn wph wch wi wi wi
    wph wps wi wn wph wch wi wi wph wps wn wch wi wi wph wps wn wph wch wi
    impexp wph wps wn wa wph wps wi wn wph wch wi wph wps annim imbi1i wph wps
    wn wph wch wi wi wi wph wph wps wn wch wi wi wi wph wps wn wch wi wi wps wn
    wph wch wi wi wph wps wn wch wi wi wph wps wn wph wch bi2.04 imbi2i wph wps
    wn wch wi pm5.4 bitr 3bitr3 wph wps wi wph wch wi df-or wps wch wo wps wn
    wch wi wph wps wch df-or imbi2i 3bitr4 $.
    $( [10-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.79 of [WhiteheadRussell] p. 121. $)
  pm4.79 $p |-  ( ( ( ps -> ph ) \/ ( ch -> ph ) ) <->
                ( ( ps /\ ch ) -> ph ) ) $=
    wph wn wps wn wi wph wn wch wn wi wo wph wn wps wch wa wn wi wps wph wi wch
    wph wi wo wps wch wa wph wi wph wn wps wn wi wph wn wch wn wi wo wph wn wps
    wn wch wn wo wi wph wn wps wch wa wn wi wph wn wps wn wch wn pm4.78 wps wch
    wa wn wps wn wch wn wo wph wn wps wch ianor imbi2i bitr4 wps wph wi wph wn
    wps wn wi wch wph wi wph wn wch wn wi wps wph pm4.1 wch wph pm4.1 orbi12i
    wps wch wa wph pm4.1 3bitr4 $.
    $( [14-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.87 of [WhiteheadRussell] p. 122.  (The proof was shortened by
     Eric Schmidt, 26-Oct-2006.) $)
  pm4.87 $p |-  ( ( ( ( ( ph /\ ps ) -> ch ) <-> ( ph -> ( ps -> ch ) ) ) /\
                ( ( ph -> ( ps -> ch ) ) <-> ( ps -> ( ph -> ch ) ) ) ) /\
                ( ( ps -> ( ph -> ch ) ) <-> ( ( ps /\ ph ) -> ch ) ) ) $=
    wph wps wa wch wi wph wps wch wi wi wb wph wps wch wi wi wps wph wch wi wi
    wb wa wps wph wch wi wi wps wph wa wch wi wb wph wps wa wch wi wph wps wch
    wi wi wb wph wps wch wi wi wps wph wch wi wi wb wph wps wch impexp wph wps
    wch bi2.04 pm3.2i wps wph wa wch wi wps wph wch wi wi wps wph wch impexp
    bicomi pm3.2i $.
    $( [27-Oct-2006] $) $( [3-Jan-2005] $)

  $( Theorem *3.33 (Syll) of [WhiteheadRussell] p. 112. $)
  pm3.33 $p |-  ( ( ( ph -> ps ) /\ ( ps -> ch ) ) -> ( ph -> ch ) ) $=
    wph wps wi wps wch wi wph wch wi wph wps wch imim1 imp $.
    $( [16-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *3.34 (Syll) of [WhiteheadRussell] p. 112. $)
  pm3.34 $p |-  ( ( ( ps -> ch ) /\ ( ph -> ps ) ) -> ( ph -> ch ) ) $=
    wps wch wi wph wps wi wph wch wi wps wch wph imim2 imp $.
    $( [16-Apr-2005] $) $( [3-Jan-2005] $)

  $( Conjunctive detachment.  Theorem *3.35 of [WhiteheadRussell] p. 112. $)
  pm3.35 $p |- ( ( ph /\ ( ph -> ps ) ) -> ps ) $=
    wph wph wps wi wps wph wps pm2.27 imp $.
    $( [14-Dec-2002] $)

  $( Theorem *5.31 of [WhiteheadRussell] p. 125. $)
  pm5.31 $p |-  ( ( ch /\ ( ph -> ps ) ) -> ( ph -> ( ps /\ ch ) ) ) $=
    wch wph wps wi wph wps wch wa wi wch wps wps wch wa wph wch wps pm3.21
    imim2d imp $.
    $( [19-Apr-2005] $) $( [3-Jan-2005] $)

  ${
    imp3.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.

    $( Importation deduction. $)
    imp3a $p |- ( ph -> ( ( ps /\ ch ) -> th ) ) $=
      wph wps wch wth wi wi wps wch wa wth wi imp3.1 wps wch wth impexp sylibr
      $.
      $( [31-Mar-1994] $)

    $( An importation inference. $)
    imp31 $p |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $=
      wph wps wa wch wth wph wps wch wth wi imp3.1 imp imp $.
      $( [26-Apr-1994] $)

    $( An importation inference. $)
    imp32 $p |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $=
      wph wps wch wa wth wph wps wch wth imp3.1 imp3a imp $.
      $( [26-Apr-1994] $)

  $}

  ${
    imp4.1 $e |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $.

    $( An importation inference. $)
    imp4a $p |- ( ph -> ( ps -> ( ( ch /\ th ) -> ta ) ) ) $=
      wph wps wch wth wta wi wi wch wth wa wta wi imp4.1 wch wth wta impexp
      syl6ibr $.
      $( [26-Apr-1994] $)

    $( An importation inference. $)
    imp4b $p |- ( ( ph /\ ps ) -> ( ( ch /\ th ) -> ta ) ) $=
      wph wps wch wth wa wta wi wph wps wch wth wta imp4.1 imp4a imp $.
      $( [26-Apr-1994] $)

    $( An importation inference. $)
    imp4c $p |- ( ph -> ( ( ( ps /\ ch ) /\ th ) -> ta ) ) $=
      wph wps wch wa wth wta wph wps wch wth wta wi imp4.1 imp3a imp3a $.
      $( [26-Apr-1994] $)

    $( An importation inference. $)
    imp4d $p |- ( ph -> ( ( ps /\ ( ch /\ th ) ) -> ta ) ) $=
      wph wps wch wth wa wta wph wps wch wth wta imp4.1 imp4a imp3a $.
      $( [26-Apr-1994] $)

    $( An importation inference. $)
    imp41 $p |- ( ( ( ( ph /\ ps ) /\ ch ) /\ th ) -> ta ) $=
      wph wps wa wch wth wta wph wps wch wth wta wi wi imp4.1 imp imp31 $.
      $( [26-Apr-1994] $)

    $( An importation inference. $)
    imp42 $p |- ( ( ( ph /\ ( ps /\ ch ) ) /\ th ) -> ta ) $=
      wph wps wch wa wa wth wta wph wps wch wth wta wi imp4.1 imp32 imp $.
      $( [26-Apr-1994] $)

    $( An importation inference. $)
    imp43 $p |- ( ( ( ph /\ ps ) /\ ( ch /\ th ) ) -> ta ) $=
      wph wps wa wch wth wa wta wph wps wch wth wta imp4.1 imp4b imp $.
      $( [26-Apr-1994] $)

    $( An importation inference. $)
    imp44 $p |- ( ( ph /\ ( ( ps /\ ch ) /\ th ) ) -> ta ) $=
      wph wps wch wa wth wa wta wph wps wch wth wta imp4.1 imp4c imp $.
      $( [26-Apr-1994] $)

    $( An importation inference. $)
    imp45 $p |- ( ( ph /\ ( ps /\ ( ch /\ th ) ) ) -> ta ) $=
      wph wps wch wth wa wa wta wph wps wch wth wta imp4.1 imp4d imp $.
      $( [26-Apr-1994] $)

  $}

  ${
    exp.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    $( Exportation inference.  (This theorem used to be labeled "exp" but was
       changed to "ex" so as not to conflict with the math token "exp", per
       the June 2006 Metamath spec change.)  (The proof was shortened by Eric
       Schmidt, 22-Dec-2006.) $)
    ex $p |- ( ph -> ( ps -> ch ) ) $=
      wph wps wa wch wi wph wps wch wi wi exp.1 wph wps wch impexp mpbi $.
      $( [22-Dec-2006] $) $( [5-Aug-1993] $)

    $( Exportation inference with commuted antecedents. $)
    expcom $p |- ( ps -> ( ph -> ch ) ) $=
      wph wps wch wph wps wch exp.1 ex com12 $.
      $( [26-May-2005] $) $( [25-May-2005] $)
  $}

  ${
    exp3a.1 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    $( Exportation deduction. $)
    exp3a $p |- ( ph -> ( ps -> ( ch -> th ) ) ) $=
      wph wps wch wa wth wi wps wch wth wi wi exp3a.1 wps wch wth impexp sylib
      $.
      $( [20-Aug-1993] $)
  $}

  ${
    exp31.1 $e |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $.
    $( An exportation inference. $)
    exp31 $p |- ( ph -> ( ps -> ( ch -> th ) ) ) $=
      wph wps wch wth wi wph wps wa wch wth exp31.1 ex ex $.
      $( [26-Apr-1994] $)
  $}

  ${
    exp32.1 $e |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $.
    $( An exportation inference. $)
    exp32 $p |- ( ph -> ( ps -> ( ch -> th ) ) ) $=
      wph wps wch wth wph wps wch wa wth exp32.1 ex exp3a $.
      $( [26-Apr-1994] $)
  $}

  ${
    exp4a.1 $e |- ( ph -> ( ps -> ( ( ch /\ th ) -> ta ) ) ) $.
    $( An exportation inference. $)
    exp4a $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wph wps wch wth wa wta wi wch wth wta wi wi exp4a.1 wch wth wta impexp
      syl6ib $.
      $( [26-Apr-1994] $)
  $}

  ${
    exp4b.1 $e |- ( ( ph /\ ps ) -> ( ( ch /\ th ) -> ta ) ) $.
    $( An exportation inference. $)
    exp4b $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wph wps wch wth wta wi wi wph wps wa wch wth wta exp4b.1 exp3a ex $.
      $( [26-Apr-1994] $)
  $}

  ${
    exp4c.1 $e |- ( ph -> ( ( ( ps /\ ch ) /\ th ) -> ta ) ) $.
    $( An exportation inference. $)
    exp4c $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wph wps wch wth wta wi wph wps wch wa wth wta exp4c.1 exp3a exp3a $.
      $( [26-Apr-1994] $)
  $}

  ${
    exp4d.1 $e |- ( ph -> ( ( ps /\ ( ch /\ th ) ) -> ta ) ) $.
    $( An exportation inference. $)
    exp4d $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wph wps wch wth wta wph wps wch wth wa wta exp4d.1 exp3a exp4a $.
      $( [26-Apr-1994] $)
  $}

  ${
    exp41.1 $e |- ( ( ( ( ph /\ ps ) /\ ch ) /\ th ) -> ta ) $.
    $( An exportation inference. $)
    exp41 $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wph wps wch wth wta wi wph wps wa wch wa wth wta exp41.1 ex exp31 $.
      $( [26-Apr-1994] $)
  $}

  ${
    exp42.1 $e |- ( ( ( ph /\ ( ps /\ ch ) ) /\ th ) -> ta ) $.
    $( An exportation inference. $)
    exp42 $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wph wps wch wth wta wi wph wps wch wa wth wta exp42.1 exp31 exp3a $.
      $( [26-Apr-1994] $)
  $}

  ${
    exp43.1 $e |- ( ( ( ph /\ ps ) /\ ( ch /\ th ) ) -> ta ) $.
    $( An exportation inference. $)
    exp43 $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wph wps wch wth wta wph wps wa wch wth wa wta exp43.1 ex exp4b $.
      $( [26-Apr-1994] $)
  $}

  ${
    exp44.1 $e |- ( ( ph /\ ( ( ps /\ ch ) /\ th ) ) -> ta ) $.
    $( An exportation inference. $)
    exp44 $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wph wps wch wth wta wi wph wps wch wa wth wta exp44.1 exp32 exp3a $.
      $( [26-Apr-1994] $)
  $}

  ${
    exp45.1 $e |- ( ( ph /\ ( ps /\ ( ch /\ th ) ) ) -> ta ) $.
    $( An exportation inference. $)
    exp45 $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wph wps wch wth wta wph wps wch wth wa wta exp45.1 exp32 exp4a $.
      $( [26-Apr-1994] $)
  $}

  ${
    impac.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Importation with conjunction in consequent. $)
    impac $p |- ( ( ph /\ ps ) -> ( ch /\ ps ) ) $=
      wph wps wch wps wa wph wps wch impac.1 ancrd imp $.
      $( [9-Aug-1994] $)
  $}

  ${
    adantl.1 $e |- ( ph -> ps ) $.
    $( Inference adding a conjunct to the left of an antecedent. $)
    adantl $p |- ( ( ch /\ ph ) -> ps ) $=
      wch wph wps wph wps wi wch adantl.1 a1i imp $.
      $( [30-Aug-1993] $)
  $}

  ${
    adantr.1 $e |- ( ph -> ps ) $.
    $( Inference adding a conjunct to the right of an antecedent. $)
    adantr $p |- ( ( ph /\ ch ) -> ps ) $=
      wph wch wps wph wps wch adantr.1 a1d imp $.
      $( [30-Aug-1993] $)
  $}

  ${
    adantld.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction adding a conjunct to the left of an antecedent. $)
    adantld $p |- ( ph -> ( ( th /\ ps ) -> ch ) ) $=
      wph wth wps wch wph wps wch wi wth adantld.1 a1d imp3a $.
      $( [4-May-1994] $)
  $}

  ${
    adantrd.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction adding a conjunct to the right of an antecedent. $)
    adantrd $p |- ( ph -> ( ( ps /\ th ) -> ch ) ) $=
      wph wps wch wps wth wa adantrd.1 wps wth pm3.26 syl5 $.
      $( [4-May-1994] $)
  $}

  ${
    adant2.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    $( Deduction adding a conjunct to antecedent. $)
    adantll $p |- ( ( ( th /\ ph ) /\ ps ) -> ch ) $=
      wth wph wa wps wch wph wps wch wi wth wph wps wch adant2.1 ex adantl imp
      $.
      $( [4-May-1994] $)

    $( Deduction adding a conjunct to antecedent. $)
    adantlr $p |- ( ( ( ph /\ th ) /\ ps ) -> ch ) $=
      wph wth wa wps wch wph wps wch wi wth wph wps wch adant2.1 ex adantr imp
      $.
      $( [4-May-1994] $)

    $( Deduction adding a conjunct to antecedent. $)
    adantrl $p |- ( ( ph /\ ( th /\ ps ) ) -> ch ) $=
      wph wth wps wa wch wph wps wch wth wph wps wch adant2.1 ex adantld imp $.
      $( [4-May-1994] $)

    $( Deduction adding a conjunct to antecedent. $)
    adantrr $p |- ( ( ph /\ ( ps /\ th ) ) -> ch ) $=
      wph wps wth wa wch wph wps wch wth wph wps wch adant2.1 ex adantrd imp $.
      $( [4-May-1994] $)
  $}

  ${
    adantl2.1 $e |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $.
    $( Deduction adding a conjunct to antecedent. $)
    adantlll $p |- ( ( ( ( ta /\ ph ) /\ ps ) /\ ch ) -> th ) $=
      wta wph wps wch wth wph wps wch wth wi wi wi wta wph wps wch wth
      adantl2.1 exp31 a1i imp41 $.
      $( [31-Dec-2004] $) $( [26-Dec-2004] $)

    $( Deduction adding a conjunct to antecedent. $)
    adantllr $p |- ( ( ( ( ph /\ ta ) /\ ps ) /\ ch ) -> th ) $=
      wph wta wps wch wth wph wps wch wth wi wi wta wph wps wch wth adantl2.1
      exp31 a1d imp41 $.
      $( [23-Apr-2005] $) $( [26-Dec-2004] $)

    $( Deduction adding a conjunct to antecedent. $)
    adantlrl $p |- ( ( ( ph /\ ( ta /\ ps ) ) /\ ch ) -> th ) $=
      wph wta wps wch wth wph wps wch wth wi wi wta wph wps wch wth adantl2.1
      exp31 a1d imp42 $.
      $( [31-Dec-2004] $) $( [26-Dec-2004] $)

    $( Deduction adding a conjunct to antecedent. $)
    adantlrr $p |- ( ( ( ph /\ ( ps /\ ta ) ) /\ ch ) -> th ) $=
      wph wps wta wch wth wph wps wch wth wi wta wph wps wch wth adantl2.1
      exp31 a1dd imp42 $.
      $( [5-Jan-2005] $) $( [26-Dec-2004] $)
  $}

  ${
    adantr2.1 $e |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $.
    $( Deduction adding a conjunct to antecedent. $)
    adantrll $p |- ( ( ph /\ ( ( ta /\ ps ) /\ ch ) ) -> th ) $=
      wph wta wps wch wth wph wps wch wth wi wi wta wph wps wch wth adantr2.1
      exp32 a1d imp44 $.
      $( [31-Dec-2004] $) $( [26-Dec-2004] $)

    $( Deduction adding a conjunct to antecedent. $)
    adantrlr $p |- ( ( ph /\ ( ( ps /\ ta ) /\ ch ) ) -> th ) $=
      wph wps wta wch wth wph wps wch wth wi wta wph wps wch wth adantr2.1
      exp32 a1dd imp44 $.
      $( [31-Dec-2004] $) $( [26-Dec-2004] $)

    $( Deduction adding a conjunct to antecedent. $)
    adantrrl $p |- ( ( ph /\ ( ps /\ ( ta /\ ch ) ) ) -> th ) $=
      wph wps wta wch wth wph wps wch wth wi wta wph wps wch wth adantr2.1
      exp32 a1dd imp45 $.
      $( [31-Dec-2004] $) $( [26-Dec-2004] $)

    $( Deduction adding a conjunct to antecedent. $)
    adantrrr $p |- ( ( ph /\ ( ps /\ ( ch /\ ta ) ) ) -> th ) $=
      wph wps wch wta wth wph wps wch wta wth wi wph wps wch wa wa wth wta
      adantr2.1 a1d exp32 imp45 $.
      $( [31-Dec-2004] $) $( [26-Dec-2004] $)
  $}

  ${
    ad2ant.1 $e |- ( ph -> ps ) $.
    $( Deduction adding conjuncts to antecedent. $)
    ad2antrr $p |- ( ( ( ph /\ ch ) /\ th ) -> ps ) $=
      wph wch wa wps wth wph wps wch ad2ant.1 adantr adantr $.
      $( [19-Oct-1999] $)

    $( Deduction adding conjuncts to antecedent. $)
    ad2antlr $p |- ( ( ( ch /\ ph ) /\ th ) -> ps ) $=
      wch wph wa wps wth wph wps wch ad2ant.1 adantl adantr $.
      $( [19-Oct-1999] $)

    $( Deduction adding conjuncts to antecedent. $)
    ad2antrl $p |- ( ( ch /\ ( ph /\ th ) ) -> ps ) $=
      wph wth wa wps wch wph wps wth ad2ant.1 adantr adantl $.
      $( [19-Oct-1999] $)

    $( Deduction adding conjuncts to antecedent. $)
    ad2antll $p |- ( ( ch /\ ( th /\ ph ) ) -> ps ) $=
      wth wph wa wps wch wph wps wth ad2ant.1 adantl adantl $.
      $( [19-Oct-1999] $)
  $}

  ${
    ad2ant2.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    $( Deduction adding two conjuncts to antecedent. $)
    ad2ant2l $p |- ( ( ( th /\ ph ) /\ ( ta /\ ps ) ) -> ch ) $=
      wph wta wps wa wch wth wph wps wch wta ad2ant2.1 adantrl adantll $.
      $( [9-Jan-2006] $) $( [8-Jan-2006] $)

    $( Deduction adding two conjuncts to antecedent. $)
    ad2ant2r $p |- ( ( ( ph /\ th ) /\ ( ps /\ ta ) ) -> ch ) $=
      wph wps wta wa wch wth wph wps wch wta ad2ant2.1 adantrr adantlr $.
      $( [9-Jan-2006] $) $( [8-Jan-2006] $)

    $( Deduction adding two conjuncts to antecedent. $)
    ad2ant2lr $p |- ( ( ( th /\ ph ) /\ ( ps /\ ta ) ) -> ch ) $=
      wph wps wta wa wch wth wph wps wch wta ad2ant2.1 adantrr adantll $.
      $( [23-Nov-2007] $) $( [23-Nov-2007] $)

    $( Deduction adding two conjuncts to antecedent. $)
    ad2ant2rl $p |- ( ( ( ph /\ th ) /\ ( ta /\ ps ) ) -> ch ) $=
      wph wta wps wa wch wth wph wps wch wta ad2ant2.1 adantrl adantlr $.
      $( [24-Nov-2007] $) $( [24-Nov-2007] $)
  $}

  $( Simplification of a conjunction. $)
  simpll $p |- ( ( ( ph /\ ps ) /\ ch ) -> ph ) $=
    wph wph wps wch wph id ad2antrr $.
    $( [19-Mar-2007] $) $( [18-Mar-2007] $)

  $( Simplification of a conjunction. $)
  simplr $p |- ( ( ( ph /\ ps ) /\ ch ) -> ps ) $=
    wps wps wph wch wps id ad2antlr $.
    $( [20-Mar-2007] $) $( [20-Mar-2007] $)

  $( Simplification of a conjunction. $)
  simprl $p |- ( ( ph /\ ( ps /\ ch ) ) -> ps ) $=
    wps wps wph wch wps id ad2antrl $.
    $( [21-Mar-2007] $) $( [21-Mar-2007] $)

  $( Simplification of a conjunction. $)
  simprr $p |- ( ( ph /\ ( ps /\ ch ) ) -> ch ) $=
    wch wch wph wps wch id ad2antll $.
    $( [21-Mar-2007] $) $( [21-Mar-2007] $)

  ${
    biimpa.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    $( Inference from a logical equivalence. $)
    biimpa $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wch wph wps wch biimpa.1 biimpd imp $.
      $( [3-May-1994] $)

    $( Inference from a logical equivalence. $)
    biimpar $p |- ( ( ph /\ ch ) -> ps ) $=
      wph wch wps wph wps wch biimpa.1 biimprd imp $.
      $( [3-May-1994] $)

    $( Inference from a logical equivalence. $)
    biimpac $p |- ( ( ps /\ ph ) -> ch ) $=
      wps wph wch wph wps wch biimpa.1 biimpcd imp $.
      $( [3-May-1994] $)

    $( Inference from a logical equivalence. $)
    biimparc $p |- ( ( ch /\ ph ) -> ps ) $=
      wch wph wps wph wps wch biimpa.1 biimprcd imp $.
      $( [3-May-1994] $)
  $}

  ${
    pm3.26bda.1 $e |- ( ph -> ( ps <-> ( ch /\ th ) ) ) $.
    $( Deduction eliminating a conjunct. $)
    pm3.26bda $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wa wch wth wph wps wch wth wa pm3.26bda.1 biimpa pm3.26d $.
      $( [23-Oct-2007] $) $( [22-Oct-2007] $)

    $( Deduction eliminating a conjunct. $)
    pm3.27bda $p |- ( ( ph /\ ps ) -> th ) $=
      wph wps wa wch wth wph wps wch wth wa pm3.26bda.1 biimpa pm3.27d $.
      $( [25-Oct-2007] $) $( [22-Oct-2007] $)
  $}

  $( Disjunction of antecedents.  Compare Theorem *4.77 of
     [WhiteheadRussell] p. 121. $)
  jaob $p |- ( ( ( ph \/ ch ) -> ps ) <-> ( ( ph -> ps ) /\ ( ch -> ps ) ) ) $=
    wph wch wo wps wi wph wps wi wch wps wi wa wph wch wo wps wi wph wps wi wch
    wps wi wph wph wch wo wps wph wch orc imim1i wch wph wch wo wps wch wph olc
    imim1i jca wph wps wi wch wps wi wph wch wo wps wi wph wps wch jao imp
    impbi $.
    $( [30-May-1994] $)

  $( Theorem *4.77 of [WhiteheadRussell] p. 121. $)
  pm4.77 $p |-  ( ( ( ps -> ph ) /\ ( ch -> ph ) ) <->
                ( ( ps \/ ch ) -> ph ) ) $=
    wps wch wo wph wi wps wph wi wch wph wi wa wps wph wch jaob bicomi $.
    $( [10-Apr-2005] $) $( [3-Jan-2005] $)

  ${
    jaod.1 $e |- ( ph -> ( ps -> ch ) ) $.
    jaod.2 $e |- ( ph -> ( th -> ch ) ) $.
    $( Deduction disjoining the antecedents of two implications. $)
    jaod $p |- ( ph -> ( ( ps \/ th ) -> ch ) ) $=
      wps wch wi wth wch wi wps wth wo wch wi wph wps wch wth jao jaod.1 jaod.2
      sylc $.
      $( [18-Aug-1994] $)
  $}

  ${
    jaoian.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    jaoian.2 $e |- ( ( th /\ ps ) -> ch ) $.
    $( Inference disjoining the antecedents of two implications. $)
    jaoian $p |- ( ( ( ph \/ th ) /\ ps ) -> ch ) $=
      wph wth wo wps wch wph wps wch wi wth wph wps wch jaoian.1 ex wth wps wch
      jaoian.2 ex jaoi imp $.
      $( [26-Oct-2005] $) $( [23-Oct-2005] $)
  $}

  ${
    jaodan.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    jaodan.2 $e |- ( ( ph /\ th ) -> ch ) $.
    $( Deduction disjoining the antecedents of two implications. $)
    jaodan $p |- ( ( ph /\ ( ps \/ th ) ) -> ch ) $=
      wph wps wth wo wch wph wps wch wth wph wps wch jaodan.1 ex wph wth wch
      jaodan.2 ex jaod imp $.
      $( [24-Oct-2005] $) $( [14-Oct-2005] $)
  $}

  ${
    jaao.1 $e |- ( ph -> ( ps -> ch ) ) $.
    jaao.2 $e |- ( th -> ( ta -> ch ) ) $.
    $( Inference conjoining and disjoining the antecedents of two
       implications. $)
    jaao $p |- ( ( ph /\ th ) -> ( ( ps \/ ta ) -> ch ) ) $=
      wph wth wa wps wch wta wph wps wch wi wth jaao.1 adantr wth wta wch wi
      wph jaao.2 adantl jaod $.
      $( [30-Sep-1999] $)
  $}

  $( Theorem *2.63 of [WhiteheadRussell] p. 107. $)
  pm2.63 $p |-  ( ( ph \/ ps ) -> ( ( -. ph \/ ps ) -> ps ) ) $=
    wph wps wo wph wn wps wps wph wps pm2.53 wph wps wo wps idd jaod $.
    $( [19-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.64 of [WhiteheadRussell] p. 107. $)
  pm2.64 $p |-  ( ( ph \/ ps ) -> ( ( ph \/ -. ps ) -> ph ) ) $=
    wph wps wn wo wph wps wo wph wph wph wps wo wph wi wps wn wph wph wps wo
    ax-1 wps wph orel2 jaoi com12 $.
    $( [19-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *3.44 of [WhiteheadRussell] p. 113. $)
  pm3.44 $p |-  ( ( ( ps -> ph ) /\ ( ch -> ph ) ) ->
                ( ( ps \/ ch ) -> ph ) ) $=
    wps wch wo wph wi wps wph wi wch wph wi wa wps wph wch jaob biimpr $.
    $( [24-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.43 of [WhiteheadRussell] p. 119. $)
  pm4.43 $p |-  ( ph <-> ( ( ph \/ ps ) /\ ( ph \/ -. ps ) ) ) $=
    wph wph wps wo wph wps wn wo wa wph wph wps wo wph wps wn wo wph wps orc
    wph wps wn orc jca wph wps wo wph wps wn wo wph wph wps pm2.64 imp impbi $.
    $( [25-Apr-2005] $) $( [3-Jan-2005] $)

  $( Idempotent law for conjunction. $)
  anidm $p |- ( ( ph /\ ph ) <-> ph ) $=
    wph wph wa wph wph wph pm3.26 wph wph wph wa wph wph pm3.2 pm2.43i impbi $.
    $( [5-Aug-1993] $)

  $( Theorem *4.24 of [WhiteheadRussell] p. 117. $)
  pm4.24 $p |-  ( ph <-> ( ph /\ ph ) ) $=
    wph wph wa wph wph anidm bicomi $.
    $( [17-Jan-2005] $) $( [3-Jan-2005] $)

  ${
    anidms.1 $e |- ( ( ph /\ ph ) -> ps ) $.
    $( Inference from idempotent law for conjunction. $)
    anidms $p |- ( ph -> ps ) $=
      wph wps wph wph wps anidms.1 ex pm2.43i $.
      $( [15-Jun-1994] $)
  $}

  $( Commutative law for conjunction.  Theorem *4.3 of [WhiteheadRussell]
     p. 118. $)
  ancom $p |- ( ( ph /\ ps ) <-> ( ps /\ ph ) ) $=
    wph wps wa wps wph wa wph wps wa wps wph wph wps pm3.27 wph wps pm3.26 jca
    wps wph wa wph wps wps wph pm3.27 wps wph pm3.26 jca impbi $.
    $( [25-Jun-1998] $)

  ${
    ancoms.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    $( Inference commuting conjunction in antecedent.  _Notational convention_:
       We sometimes suffix with "s" the label of an inference that manipulates
       an antecedent, leaving the consequent unchanged.  The "s" means that the
       inference eliminates the need for a syllogism ( ~ syl ) -type inference
       in a proof. $)
    ancoms $p |- ( ( ps /\ ph ) -> ch ) $=
      wps wph wa wph wps wa wch wps wph ancom ancoms.1 sylbi $.
      $( [21-Apr-1994] $)
  $}

  ${
    ancomsd.1 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    $( Deduction commuting conjunction in antecedent. $)
    ancomsd $p |- ( ph -> ( ( ch /\ ps ) -> th ) ) $=
      wph wps wch wa wth wch wps wa ancomsd.1 wch wps ancom syl5ib $.
      $( [13-Dec-2004] $) $( [12-Dec-2004] $)
  $}

  $( Theorem *3.22 of [WhiteheadRussell] p. 111. $)
  pm3.22 $p |-  ( ( ph /\ ps ) -> ( ps /\ ph ) ) $=
    wph wps wa wps wph wa wph wps ancom biimp $.
    $( [17-Jan-2005] $) $( [3-Jan-2005] $)

  $( Associative law for conjunction.  Theorem *4.32 of [WhiteheadRussell]
     p. 118. $)
  anass $p |- ( ( ( ph /\ ps ) /\ ch ) <-> ( ph /\ ( ps /\ ch ) ) ) $=
    wph wps wa wch wn wi wn wph wps wch wa wn wi wn wph wps wa wch wa wph wps
    wch wa wa wph wps wa wch wn wi wph wps wch wa wn wi wph wps wa wch wn wi
    wph wps wch wn wi wi wph wps wch wa wn wi wph wps wch wn impexp wps wch wn
    wi wps wch wa wn wph wps wch imnan imbi2i bitr negbii wph wps wa wch df-an
    wph wps wch wa df-an 3bitr4 $.
    $( [5-Aug-1993] $)

  ${
    anasss.1 $e |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $.
    $( Associative law for conjunction applied to antecedent (eliminates
       syllogism). $)
    anasss $p |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $=
      wph wps wch wth wph wps wch wth anasss.1 exp31 imp32 $.
      $( [15-Nov-2002] $)
  $}

  ${
    anassrs.1 $e |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $.
    $( Associative law for conjunction applied to antecedent (eliminates
       syllogism). $)
    anassrs $p |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $=
      wph wps wch wth wph wps wch wth anassrs.1 exp32 imp31 $.
      $( [15-Nov-2002] $)
  $}

  $( Distribution of implication with conjunction. $)
  imdistan $p |- ( ( ph -> ( ps -> ch ) ) <->
                 ( ( ph /\ ps ) -> ( ph /\ ch ) ) ) $=
    wph wps wch wi wi wph wps wa wph wch wa wi wph wps wch wi wi wph wps wph
    wch wa wph wps wch anc2l imp3a wph wps wa wph wch wa wi wph wps wch wph wch
    wa wch wph wps wa wph wch pm3.27 imim2i exp3a impbi $.
    $( [31-May-1999] $)

  ${
    imdistani.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Distribution of implication with conjunction. $)
    imdistani $p |- ( ( ph /\ ps ) -> ( ph /\ ch ) ) $=
      wph wps wph wch wa wph wps wch imdistani.1 anc2li imp $.
      $( [1-Aug-1994] $)
  $}

  ${
    imdistanri.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Distribution of implication with conjunction. $)
    imdistanri $p |- ( ( ps /\ ph ) -> ( ch /\ ph ) ) $=
      wps wph wch wph wps wch imdistanri.1 com12 impac $.
      $( [8-Jan-2002] $)
  $}

  ${
    imdistand.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( Distribution of implication with conjunction (deduction rule). $)
    imdistand $p |- ( ph -> ( ( ps /\ ch ) -> ( ps /\ th ) ) ) $=
      wph wps wch wth wi wi wps wch wa wps wth wa wi imdistand.1 wps wch wth
      imdistan sylib $.
      $( [28-Aug-2004] $) $( [27-Aug-2004] $)
  $}

  $( Theorem *5.3 of [WhiteheadRussell] p. 125. $)
  pm5.3 $p |-  ( ( ( ph /\ ps ) -> ch ) <->
               ( ( ph /\ ps ) -> ( ph /\ ch ) ) ) $=
    wph wps wa wch wi wph wps wa wph wch wa wi wph wps wa wch wi wph wps wch
    wph wps wch pm3.3 imdistand wph wch wa wch wph wps wa wph wch pm3.27 imim2i
    impbi $.
    $( [27-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.61 of [WhiteheadRussell] p. 125. $)
  pm5.61 $p |-  ( ( ( ph \/ ps ) /\ -. ps ) <-> ( ph /\ -. ps ) ) $=
    wph wps wo wps wn wa wph wps wn wa wps wn wph wps wo wph wps wph orel2
    imdistanri wph wph wps wo wps wn wph wps orc anim1i impbi $.
    $( [10-Apr-2005] $) $( [3-Jan-2005] $)

  ${
    sylan.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    ${
      sylan.2 $e |- ( th -> ph ) $.
      $( A syllogism inference. $)
      sylan $p |- ( ( th /\ ps ) -> ch ) $=
        wth wps wch wth wph wps wch wi sylan.2 wph wps wch sylan.1 ex syl imp
        $.
        $( [21-Apr-1994] $)
    $}

    ${
      sylanb.2 $e |- ( th <-> ph ) $.
      $( A syllogism inference. $)
      sylanb $p |- ( ( th /\ ps ) -> ch ) $=
        wph wps wch wth sylan.1 wth wph sylanb.2 biimp sylan $.
        $( [18-May-1994] $)
    $}

    ${
      sylanbr.2 $e |- ( ph <-> th ) $.
      $( A syllogism inference. $)
      sylanbr $p |- ( ( th /\ ps ) -> ch ) $=
        wph wps wch wth sylan.1 wph wth sylanbr.2 biimpr sylan $.
        $( [18-May-1994] $)
    $}

    ${
      sylan2.2 $e |- ( th -> ps ) $.
      $( A syllogism inference. $)
      sylan2 $p |- ( ( ph /\ th ) -> ch ) $=
        wph wth wch wph wps wch wth wph wps wch sylan.1 ex sylan2.2 syl5 imp $.
        $( [21-Apr-1994] $)
    $}

    ${
      sylan2b.2 $e |- ( th <-> ps ) $.
      $( A syllogism inference. $)
      sylan2b $p |- ( ( ph /\ th ) -> ch ) $=
        wph wps wch wth sylan.1 wth wps sylan2b.2 biimp sylan2 $.
        $( [21-Apr-1994] $)
    $}

    ${
      sylan2br.2 $e |- ( ps <-> th ) $.
      $( A syllogism inference. $)
      sylan2br $p |- ( ( ph /\ th ) -> ch ) $=
        wph wps wch wth sylan.1 wps wth sylan2br.2 biimpr sylan2 $.
        $( [21-Apr-1994] $)
    $}

    ${
      syl2an.2 $e |- ( th -> ph ) $.
      syl2an.3 $e |- ( ta -> ps ) $.
      $( A double syllogism inference. $)
      syl2an $p |- ( ( th /\ ta ) -> ch ) $=
        wth wps wch wta wph wps wch wth sylan.1 syl2an.2 sylan syl2an.3 sylan2
        $.
        $( [31-Jan-1997] $)
    $}

    ${
      syl2anb.2 $e |- ( th <-> ph ) $.
      syl2anb.3 $e |- ( ta <-> ps ) $.
      $( A double syllogism inference. $)
      syl2anb $p |- ( ( th /\ ta ) -> ch ) $=
        wth wps wch wta wph wps wch wth sylan.1 syl2anb.2 sylanb syl2anb.3
        sylan2b $.
        $( [29-Jul-1999] $)
    $}

    ${
      syl2anbr.2 $e |- ( ph <-> th ) $.
      syl2anbr.3 $e |- ( ps <-> ta ) $.
      $( A double syllogism inference. $)
      syl2anbr $p |- ( ( th /\ ta ) -> ch ) $=
        wth wps wch wta wph wps wch wth sylan.1 syl2anbr.2 sylanbr syl2anbr.3
        sylan2br $.
        $( [29-Jul-1999] $)
    $}
  $}

  ${
    syland.1 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    syland.2 $e |- ( ph -> ( ta -> ps ) ) $.
    $( A syllogism deduction. $)
    syland $p |- ( ph -> ( ( ta /\ ch ) -> th ) ) $=
      wph wta wch wth wph wta wps wch wth wi syland.2 wph wps wch wth syland.1
      exp3a syld imp3a $.
      $( [17-Dec-2004] $) $( [15-Dec-2004] $)
  $}

  ${
    sylan2d.1 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    sylan2d.2 $e |- ( ph -> ( ta -> ch ) ) $.
    $( A syllogism deduction. $)
    sylan2d $p |- ( ph -> ( ( ps /\ ta ) -> th ) ) $=
      wph wta wps wth wph wch wps wth wta wph wps wch wth sylan2d.1 ancomsd
      sylan2d.2 syland ancomsd $.
      $( [17-Dec-2004] $) $( [15-Dec-2004] $)
  $}

  ${
    $v et $. $( Greek eta $)
    syl2and.wet $f wff et $.
    syl2and.1 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    syl2and.2 $e |- ( ph -> ( ta -> ps ) ) $.
    syl2and.3 $e |- ( ph -> ( et -> ch ) ) $.
    $( A syllogism deduction. $)
    syl2and $p |- ( ph -> ( ( ta /\ et ) -> th ) ) $=
      wph wps syl2and.wet wth wta wph wps wch wth syl2and.wet syl2and.1
      syl2and.3 sylan2d syl2and.2 syland $.
      $( [17-Dec-2004] $) $( [15-Dec-2004] $)
  $}

  ${
    sylanl1.1 $e |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $.
    sylanl1.2 $e |- ( ta -> ph ) $.
    $( A syllogism inference. $)
    sylanl1 $p |- ( ( ( ta /\ ps ) /\ ch ) -> th ) $=
      wph wps wa wch wth wta wps wa sylanl1.1 wta wph wps sylanl1.2 anim1i
      sylan $.
      $( [30-Apr-2005] $) $( [10-Mar-2005] $)
  $}

  ${
    sylanl2.1 $e |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $.
    sylanl2.2 $e |- ( ta -> ps ) $.
    $( A syllogism inference. $)
    sylanl2 $p |- ( ( ( ph /\ ta ) /\ ch ) -> th ) $=
      wph wps wa wch wth wph wta wa sylanl2.1 wta wps wph sylanl2.2 anim2i
      sylan $.
      $( [2-Jan-2005] $) $( [1-Jan-2005] $)
  $}

  ${
    sylanr1.1 $e |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $.
    sylanr1.2 $e |- ( ta -> ps ) $.
    $( A syllogism inference. $)
    sylanr1 $p |- ( ( ph /\ ( ta /\ ch ) ) -> th ) $=
      wph wps wch wa wth wta wch wa sylanr1.1 wta wps wch sylanr1.2 anim1i
      sylan2 $.
      $( [15-May-2005] $) $( [9-Apr-2005] $)
  $}

  ${
    sylanr2.1 $e |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $.
    sylanr2.2 $e |- ( ta -> ch ) $.
    $( A syllogism inference. $)
    sylanr2 $p |- ( ( ph /\ ( ps /\ ta ) ) -> th ) $=
      wph wps wch wa wth wps wta wa sylanr2.1 wta wch wps sylanr2.2 anim2i
      sylan2 $.
      $( [1-May-2005] $) $( [9-Apr-2005] $)
  $}

  ${
    sylani.1 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    sylani.2 $e |- ( ta -> ps ) $.
    $( A syllogism inference. $)
    sylani $p |- ( ph -> ( ( ta /\ ch ) -> th ) ) $=
      wph wps wch wth wta sylani.1 wta wps wi wph sylani.2 a1i syland $.
      $( [2-May-1996] $)
  $}

  ${
    sylan2i.1 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    sylan2i.2 $e |- ( ta -> ch ) $.
    $( A syllogism inference. $)
    sylan2i $p |- ( ph -> ( ( ps /\ ta ) -> th ) ) $=
      wph wps wch wth wta sylan2i.1 wta wch wi wph sylan2i.2 a1i sylan2d $.
      $( [1-Aug-1994] $)
  $}

  ${
    $v et $. $( Greek eta $)
    syl2ani.wet $f wff et $.
    syl2ani.1 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    syl2ani.2 $e |- ( ta -> ps ) $.
    syl2ani.3 $e |- ( et -> ch ) $.
    $( A syllogism inference. $)
    syl2ani $p |- ( ph -> ( ( ta /\ et ) -> th ) ) $=
      wph wps syl2ani.wet wth wta wph wps wch wth syl2ani.wet syl2ani.1
      syl2ani.3 sylan2i syl2ani.2 sylani $.
      $( [3-Aug-1999] $)
  $}

  ${
    syldan.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    syldan.2 $e |- ( ( ph /\ ch ) -> th ) $.
    $( A syllogism deduction with conjoined antecents. $)
    syldan $p |- ( ( ph /\ ps ) -> th ) $=
      wph wps wth wph wps wch wth wph wps wch syldan.1 ex wph wch wth syldan.2
      ex syld imp $.
      $( [26-Feb-2005] $) $( [24-Feb-2005] $)
  $}

  ${
    sylan9.1 $e |- ( ph -> ( ps -> ch ) ) $.
    sylan9.2 $e |- ( th -> ( ch -> ta ) ) $.
    $( Nested syllogism inference conjoining dissimilar antecedents. $)
    sylan9 $p |- ( ( ph /\ th ) -> ( ps -> ta ) ) $=
      wph wth wa wps wch wta wph wps wch wi wth sylan9.1 adantr wth wch wta wi
      wph sylan9.2 adantl syld $.
      $( [5-Aug-1993] $)
  $}

  ${
    sylan9r.1 $e |- ( ph -> ( ps -> ch ) ) $.
    sylan9r.2 $e |- ( th -> ( ch -> ta ) ) $.
    $( Nested syllogism inference conjoining dissimilar antecedents. $)
    sylan9r $p |- ( ( th /\ ph ) -> ( ps -> ta ) ) $=
      wth wph wps wta wi wph wps wch wth wta sylan9r.1 sylan9r.2 syl9r imp $.
      $( [5-Aug-1993] $)
  $}

  ${
    mpan9.1 $e |- ( ph -> ps ) $.
    mpan9.2 $e |- ( ch -> ( ps -> th ) ) $.
    $( Modus ponens conjoining dissimilar antecedents. $)
    mpan9 $p |- ( ( ph /\ ch ) -> th ) $=
      wph wch wa wps wth wph wps wch mpan9.1 adantr wch wps wth wi wph mpan9.2
      adantl mpd $.
      $( [1-Feb-2008] $) $( [1-Feb-2008] $)
  $}

  ${
    sylanc.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    sylanc.2 $e |- ( th -> ph ) $.
    sylanc.3 $e |- ( th -> ps ) $.
    $( A syllogism inference combined with contraction. $)
    sylanc $p |- ( th -> ch ) $=
      wph wps wch wth wph wps wch sylanc.1 ex sylanc.2 sylanc.3 sylc $.
      $( [3-Oct-1999] $)
  $}

  ${
    $v et $. $( Greek eta $)
    syl2anc.wet $f wff et $.
    syl2anc.1 $e |- ( ( ( ph /\ ps ) /\ ( ch /\ th ) ) -> ta ) $.
    syl2anc.2 $e |- ( et -> ph ) $.
    syl2anc.3 $e |- ( et -> ps ) $.
    syl2anc.4 $e |- ( et -> ch ) $.
    syl2anc.5 $e |- ( et -> th ) $.
    $( A syllogism inference combined with contraction. $)
    syl2anc $p |- ( et -> ta ) $=
      wph wps wa wch wth wa wta syl2anc.wet syl2anc.1 syl2anc.wet wph wps
      syl2anc.2 syl2anc.3 jca syl2anc.wet wch wth syl2anc.4 syl2anc.5 jca
      sylanc $.
      $( [18-Jun-2007] $) $( [16-Jun-2007] $)
  $}

  ${
    sylancb.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    sylancb.2 $e |- ( th <-> ph ) $.
    sylancb.3 $e |- ( th <-> ps ) $.
    $( A syllogism inference combined with contraction. $)
    sylancb $p |- ( th -> ch ) $=
      wth wch wph wps wch wth wth sylancb.1 sylancb.2 sylancb.3 syl2anb anidms
      $.
      $( [9-Sep-2004] $) $( [3-Sep-2004] $)
  $}

  ${
    sylancbr.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    sylancbr.2 $e |- ( ph <-> th ) $.
    sylancbr.3 $e |- ( ps <-> th ) $.
    $( A syllogism inference combined with contraction. $)
    sylancbr $p |- ( th -> ch ) $=
      wth wch wph wps wch wth wth sylancbr.1 sylancbr.2 sylancbr.3 syl2anbr
      anidms $.
      $( [14-Sep-2004] $) $( [3-Sep-2004] $)
  $}

  ${
    pm2.61ian.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    pm2.61ian.2 $e |- ( ( -. ph /\ ps ) -> ch ) $.
    $( Elimination of an antecedent. $)
    pm2.61ian $p |- ( ps -> ch ) $=
      wph wps wch wi wph wps wch pm2.61ian.1 ex wph wn wps wch pm2.61ian.2 ex
      pm2.61i $.
      $( [3-Jan-2005] $) $( [1-Jan-2005] $)
  $}

  ${
    pm2.61dan.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    pm2.61dan.2 $e |- ( ( ph /\ -. ps ) -> ch ) $.
    $( Elimination of an antecedent. $)
    pm2.61dan $p |- ( ph -> ch ) $=
      wph wps wch wph wps wch pm2.61dan.1 ex wph wps wn wch pm2.61dan.2 ex
      pm2.61d $.
      $( [3-Jan-2005] $) $( [1-Jan-2005] $)
  $}

  ${
    condan.1 $e |- ( ( ph /\ -. ps ) -> ch ) $.
    condan.2 $e |- ( ( ph /\ -. ps ) -> -. ch ) $.
    $( Proof by contradiction. $)
    condan $p |- ( ph -> ps ) $=
      wph wps wn wn wps wph wps wn wch wph wps wn wch condan.1 ex wph wps wn
      wch wn condan.2 ex pm2.65d wps nega syl $.
      $( [21-Feb-2006] $) $( [9-Feb-2006] $)
  $}

  $( Introduce one conjunct as an antecedent to the another. $)
  abai $p |- ( ( ph /\ ps ) <-> ( ph /\ ( ph -> ps ) ) ) $=
    wph wps wa wph wph wps wi wa wph wps wa wph wph wps wi wph wps pm3.26 wph
    wps pm3.4 jca wph wph wps wi wa wph wps wph wph wps wi pm3.26 wph wps
    pm3.35 jca impbi $.
    $( [12-Aug-1993] $)

  ${
    bi.aa $e |- ( ph <-> ps ) $.

    $( Introduce a left conjunct to both sides of a logical equivalence. $)
    anbi2i $p |- ( ( ch /\ ph ) <-> ( ch /\ ps ) ) $=
      wch wph wa wch wps wa wph wps wch wph wps bi.aa biimp anim2i wps wph wch
      wph wps bi.aa biimpr anim2i impbi $.
      $( [5-Aug-1993] $)

    $( Introduce a right conjunct to both sides of a logical equivalence. $)
    anbi1i $p |- ( ( ph /\ ch ) <-> ( ps /\ ch ) ) $=
      wph wch wa wch wph wa wch wps wa wps wch wa wph wch ancom wph wps wch
      bi.aa anbi2i wch wps ancom 3bitr $.
      $( [5-Aug-1993] $)
  $}

  ${
    anbi12.1 $e |- ( ph <-> ps ) $.
    anbi12.2 $e |- ( ch <-> th ) $.
    $( Conjoin both sides of two equivalences. $)
    anbi12i $p |- ( ( ph /\ ch ) <-> ( ps /\ th ) ) $=
      wph wch wa wps wch wa wps wth wa wph wps wch anbi12.1 anbi1i wch wth wps
      anbi12.2 anbi2i bitr $.
      $( [5-Aug-1993] $)
  $}

  $( Theorem *5.53 of [WhiteheadRussell] p. 125. $)
  pm5.53 $p |-  ( ( ( ( ph \/ ps ) \/ ch ) -> th ) <->
                ( ( ( ph -> th ) /\ ( ps -> th ) ) /\ ( ch -> th ) ) ) $=
    wph wps wo wch wo wth wi wph wps wo wth wi wch wth wi wa wph wth wi wps wth
    wi wa wch wth wi wa wph wps wo wth wch jaob wph wps wo wth wi wph wth wi
    wps wth wi wa wch wth wi wph wth wps jaob anbi1i bitr $.
    $( [28-Apr-2005] $) $( [3-Jan-2005] $)

  $( A rearrangement of conjuncts. $)
  an12 $p |- ( ( ph /\ ( ps /\ ch ) ) <-> ( ps /\ ( ph /\ ch ) ) ) $=
    wph wps wa wch wa wps wph wa wch wa wph wps wch wa wa wps wph wch wa wa wph
    wps wa wps wph wa wch wph wps ancom anbi1i wph wps wch anass wps wph wch
    anass 3bitr3 $.
    $( [12-Mar-1995] $)

  $( A rearrangement of conjuncts. $)
  an23 $p |- ( ( ( ph /\ ps ) /\ ch ) <-> ( ( ph /\ ch ) /\ ps ) ) $=
    wph wps wch wa wa wph wch wps wa wa wph wps wa wch wa wph wch wa wps wa wps
    wch wa wch wps wa wph wps wch ancom anbi2i wph wps wch anass wph wch wps
    anass 3bitr4 $.
    $( [12-Mar-1995] $)

  ${
    an1s.1 $e |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $.
    $( Deduction rearranging conjuncts. $)
    an1s $p |- ( ( ps /\ ( ph /\ ch ) ) -> th ) $=
      wps wph wch wa wa wph wps wch wa wa wth wps wph wch an12 an1s.1 sylbi $.
      $( [13-Mar-1996] $)

    $( Inference commuting a nested conjunction in antecedent. $)
    ancom2s $p |- ( ( ph /\ ( ch /\ ps ) ) -> th ) $=
      wph wch wps wth wph wps wch wth wph wps wch wth an1s.1 exp32 com23 imp32
      $.
      $( [25-May-2006] $) $( [24-May-2006] $)

    $( Deduction rearranging conjuncts. $)
    ancom13s $p |- ( ( ch /\ ( ps /\ ph ) ) -> th ) $=
      wch wps wph wth wph wps wch wth wph wps wch wth an1s.1 exp32 com13 imp32
      $.
      $( [31-May-2006] $) $( [31-May-2006] $)
  $}

  ${
    an1rs.1 $e |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $.
    $( Deduction rearranging conjuncts. $)
    an1rs $p |- ( ( ( ph /\ ch ) /\ ps ) -> th ) $=
      wph wch wa wps wa wph wps wa wch wa wth wph wch wps an23 an1rs.1 sylbi $.
      $( [13-Mar-1996] $)

    $( Inference commuting a nested conjunction in antecedent. $)
    ancom1s $p |- ( ( ( ps /\ ph ) /\ ch ) -> th ) $=
      wps wph wch wth wph wps wch wth wi wph wps wch wth an1rs.1 exp31 com12
      imp31 $.
      $( [25-May-2006] $) $( [24-May-2006] $)

    $( Deduction rearranging conjuncts. $)
    ancom31s $p |- ( ( ( ch /\ ps ) /\ ph ) -> th ) $=
      wch wps wph wth wph wps wch wth wph wps wch wth an1rs.1 exp31 com13 imp31
      $.
      $( [2-Jun-2006] $) $( [31-May-2006] $)
  $}

  $( Absorption into embedded conjunct. $)
  anabs1 $p |- ( ( ( ph /\ ps ) /\ ph ) <-> ( ph /\ ps ) ) $=
    wph wps wa wph wa wph wps wa wph wps wa wph pm3.26 wph wps wa wph wph wps
    pm3.26 ancli impbi $.
    $( [4-Sep-1995] $)

  $( Absorption into embedded conjunct. $)
  anabs5 $p |- ( ( ph /\ ( ph /\ ps ) ) <-> ( ph /\ ps ) ) $=
    wph wph wps wa wa wph wps wa wph wa wph wps wa wph wps wa wph ancom wph wps
    anabs1 bitr3 $.
    $( [20-Jul-1996] $)

  $( Absorption into embedded conjunct. $)
  anabs7 $p |- ( ( ps /\ ( ph /\ ps ) ) <-> ( ph /\ ps ) ) $=
    wps wph wps wa wa wph wps wa wps wph wps wa pm3.27 wph wps wa wps wph wps
    pm3.27 ancri impbi $.
    $( [20-Jul-1996] $)

  ${
    anabsi5.1 $e |- ( ph -> ( ( ph /\ ps ) -> ch ) ) $.
    $( Absorption of antecedent into conjunction. $)
    anabsi5 $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wa wch wph wph wps wa wch wi wps anabsi5.1 adantr pm2.43i $.
      $( [11-Jun-1995] $)
  $}

  ${
    anabsi6.1 $e |- ( ph -> ( ( ps /\ ph ) -> ch ) ) $.
    $( Absorption of antecedent into conjunction. $)
    anabsi6 $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wch wph wps wph wch anabsi6.1 ancomsd anabsi5 $.
      $( [14-Aug-2000] $)
  $}

  ${
    anabsi7.1 $e |- ( ps -> ( ( ph /\ ps ) -> ch ) ) $.
    $( Absorption of antecedent into conjunction. $)
    anabsi7 $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wch wph wps wch wps wph wps wch anabsi7.1 exp3a pm2.43b imp $.
      $( [20-Jul-1996] $)
  $}

  ${
    anabsi8.1 $e |- ( ps -> ( ( ps /\ ph ) -> ch ) ) $.
    $( Absorption of antecedent into conjunction. $)
    anabsi8 $p |- ( ( ph /\ ps ) -> ch ) $=
      wps wph wch wps wph wch anabsi8.1 anabsi5 ancoms $.
      $( [26-Sep-1999] $)
  $}

  ${
    anabss1.1 $e |- ( ( ( ph /\ ps ) /\ ph ) -> ch ) $.
    $( Absorption of antecedent into conjunction. $)
    anabss1 $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wa wch wph wps wa wph wch wps anabss1.1 adantrr anidms $.
      $( [20-Jul-1996] $)
  $}

  ${
    anabss3.1 $e |- ( ( ( ph /\ ps ) /\ ps ) -> ch ) $.
    $( Absorption of antecedent into conjunction. $)
    anabss3 $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wa wch wph wps wa wps wch wph anabss3.1 adantrl anidms $.
      $( [20-Jul-1996] $)
  $}

  ${
    anabss4.1 $e |- ( ( ( ps /\ ph ) /\ ps ) -> ch ) $.
    $( Absorption of antecedent into conjunction. $)
    anabss4 $p |- ( ( ph /\ ps ) -> ch ) $=
      wps wph wch wps wph wch anabss4.1 anabss1 ancoms $.
      $( [20-Jul-1996] $)
  $}

  ${
    anabss5.1 $e |- ( ( ph /\ ( ph /\ ps ) ) -> ch ) $.
    $( Absorption of antecedent into conjunction. $)
    anabss5 $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wa wch wph wph wps wa wch wps anabss5.1 adantlr anidms $.
      $( [10-May-1994] $)
  $}

  ${
    anabss7.1 $e |- ( ( ps /\ ( ph /\ ps ) ) -> ch ) $.
    $( Absorption of antecedent into conjunction. $)
    anabss7 $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wch wps wph wps wa wch anabss7.1 ex anabsi7 $.
      $( [20-Jul-1996] $)
  $}

  ${
    anabsan.1 $e |- ( ( ( ph /\ ph ) /\ ps ) -> ch ) $.
    $( Absorption of antecedent with conjunction. $)
    anabsan $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wch wph wph wps wch anabsan.1 an1rs anabss1 $.
      $( [24-Mar-1996] $)
  $}

  ${
    anabsan2.1 $e |- ( ( ph /\ ( ps /\ ps ) ) -> ch ) $.
    $( Absorption of antecedent with conjunction. $)
    anabsan2 $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wch wph wps wps wch anabsan2.1 anassrs anabss3 $.
      $( [10-May-2004] $) $( [10-May-2004] $)
  $}

  $( Rearrangement of 4 conjuncts. $)
  an4 $p |- ( ( ( ph /\ ps ) /\ ( ch /\ th ) ) <->
              ( ( ph /\ ch ) /\ ( ps /\ th ) ) ) $=
    wph wps wch wth wa wa wa wph wch wps wth wa wa wa wph wps wa wch wth wa wa
    wph wch wa wps wth wa wa wps wch wth wa wa wch wps wth wa wa wph wps wch
    wth an12 anbi2i wph wps wch wth wa anass wph wch wps wth wa anass 3bitr4 $.
    $( [10-Jul-1994] $)

  $( Rearrangement of 4 conjuncts. $)
  an42 $p |- ( ( ( ph /\ ps ) /\ ( ch /\ th ) ) <->
                 ( ( ph /\ ch ) /\ ( th /\ ps ) ) ) $=
    wph wps wa wch wth wa wa wph wch wa wps wth wa wa wph wch wa wth wps wa wa
    wph wps wch wth an4 wps wth wa wth wps wa wph wch wa wps wth ancom anbi2i
    bitr $.
    $( [7-Feb-1996] $)

  ${
    an4s.1 $e |- ( ( ( ph /\ ps ) /\ ( ch /\ th ) ) -> ta ) $.
    $( Inference rearranging 4 conjuncts in antecedent. $)
    an4s $p |- ( ( ( ph /\ ch ) /\ ( ps /\ th ) ) -> ta ) $=
      wph wch wa wps wth wa wa wph wps wa wch wth wa wa wta wph wch wps wth an4
      an4s.1 sylbi $.
      $( [10-Aug-1995] $)
  $}

  ${
    an41r3s.1 $e |- ( ( ( ph /\ ps ) /\ ( ch /\ th ) ) -> ta ) $.
    $( Inference rearranging 4 conjuncts in antecedent. $)
    an42s $p |- ( ( ( ph /\ ch ) /\ ( th /\ ps ) ) -> ta ) $=
      wph wch wa wth wps wa wa wph wps wa wch wth wa wa wta wph wps wch wth
      an42 an41r3s.1 sylbir $.
      $( [10-Aug-1995] $)
  $}

  $( Distribution of conjunction over conjunction. $)
  anandi $p |- ( ( ph /\ ( ps /\ ch ) ) <->
               ( ( ph /\ ps ) /\ ( ph /\ ch ) ) ) $=
    wph wps wch wa wa wph wph wa wps wch wa wa wph wps wa wph wch wa wa wph wph
    wa wph wps wch wa wph anidm anbi1i wph wph wps wch an4 bitr3 $.
    $( [14-Aug-1995] $)

  $( Distribution of conjunction over conjunction. $)
  anandir $p |- ( ( ( ph /\ ps ) /\ ch ) <->
               ( ( ph /\ ch ) /\ ( ps /\ ch ) ) ) $=
    wph wps wa wch wa wph wps wa wch wch wa wa wph wch wa wps wch wa wa wch wch
    wa wch wph wps wa wch anidm anbi2i wph wps wch wch an4 bitr3 $.
    $( [24-Aug-1995] $)

  ${
    anandis.1 $e |- ( ( ( ph /\ ps ) /\ ( ph /\ ch ) ) -> ta ) $.
    $( Inference that undistributes conjunction in the antecedent. $)
    anandis $p |- ( ( ph /\ ( ps /\ ch ) ) -> ta ) $=
      wph wps wch wa wta wph wps wph wch wta anandis.1 an4s anabsan $.
      $( [7-Jun-2004] $) $( [7-Jun-2004] $)
  $}

  ${
    anandirs.1 $e |- ( ( ( ph /\ ch ) /\ ( ps /\ ch ) ) -> ta ) $.
    $( Inference that undistributes conjunction in the antecedent. $)
    anandirs $p |- ( ( ( ph /\ ps ) /\ ch ) -> ta ) $=
      wph wps wa wch wta wph wch wps wch wta anandirs.1 an4s anabsan2 $.
      $( [8-Jun-2004] $) $( [7-Jun-2004] $)
  $}

  $( A theorem similar to the standard definition of the biconditional.
     Definition of [Margaris] p. 49. $)
  bi $p |- ( ( ph <-> ps ) <-> ( ( ph -> ps ) /\ ( ps -> ph ) ) ) $=
    wph wps wb wph wps wi wps wph wi wn wi wn wph wps wi wps wph wi wa wph wps
    bii wph wps wi wps wph wi df-an bitr4 $.
    $( [5-Aug-1993] $)

  ${
    impbid.1 $e |- ( ph -> ( ps -> ch ) ) $.
    impbid.2 $e |- ( ph -> ( ch -> ps ) ) $.
    $( Deduce an equivalence from two implications. $)
    impbid $p |- ( ph -> ( ps <-> ch ) ) $=
      wph wps wch wi wch wps wi wa wps wch wb wph wps wch wi wch wps wi
      impbid.1 impbid.2 jca wps wch bi sylibr $.
      $( [5-Aug-1993] $)
  $}

  ${
    impbid1.1 $e |- ( ph -> ( ps -> ch ) ) $.
    impbid1.2 $e |- ( ch -> ps ) $.
    $( Infer an equivalence from two implications. $)
    impbid1 $p |- ( ph -> ( ps <-> ch ) ) $=
      wph wps wch impbid1.1 wch wps wi wph impbid1.2 a1i impbid $.
      $( [7-Mar-2007] $) $( [6-Mar-2007] $)
  $}

  ${
    impbid2.1 $e |- ( ps -> ch ) $.
    impbid2.2 $e |- ( ph -> ( ch -> ps ) ) $.
    $( Infer an equivalence from two implications. $)
    impbid2 $p |- ( ph -> ( ps <-> ch ) ) $=
      wph wps wch wps wch wi wph impbid2.1 a1i impbid2.2 impbid $.
      $( [7-Mar-2007] $) $( [6-Mar-2007] $)
  $}

  ${
    impbida.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    impbida.2 $e |- ( ( ph /\ ch ) -> ps ) $.
    $( Deduce an equivalence from two implications. $)
    impbida $p |- ( ph -> ( ps <-> ch ) ) $=
      wph wps wch wph wps wch impbida.1 ex wph wch wps impbida.2 ex impbid $.
      $( [20-Feb-2007] $) $( [17-Feb-2007] $)
  $}

  $( Commutative law for equivalence.  Theorem *4.21 of [WhiteheadRussell]
     p. 117. $)
  bicom $p |- ( ( ph <-> ps ) <-> ( ps <-> ph ) ) $=
    wph wps wi wps wph wi wa wps wph wi wph wps wi wa wph wps wb wps wph wb wph
    wps wi wps wph wi ancom wph wps bi wps wph bi 3bitr4 $.
    $( [5-Aug-1993] $)

  ${
    bicomd.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    $( Commute two sides of a biconditional in a deduction. $)
    bicomd $p |- ( ph -> ( ch <-> ps ) ) $=
      wph wps wch wb wch wps wb bicomd.1 wps wch bicom sylib $.
      $( [5-Aug-1993] $)
  $}

  $( Contraposition.  Theorem *4.11 of [WhiteheadRussell] p. 117. $)
  pm4.11 $p |- ( ( ph <-> ps ) <-> ( -. ph <-> -. ps ) ) $=
    wph wps wb wps wn wph wn wb wph wn wps wn wb wph wps wi wps wph wi wa wps
    wn wph wn wi wph wn wps wn wi wa wph wps wb wps wn wph wn wb wph wps wi wps
    wn wph wn wi wps wph wi wph wn wps wn wi wph wps pm4.1 wps wph pm4.1
    anbi12i wph wps bi wps wn wph wn bi 3bitr4 wps wn wph wn bicom bitr $.
    $( [21-May-1994] $)

  ${
    con4bii.1 $e |- ( -. ph <-> -. ps ) $.
    $( A contraposition inference. $)
    con4bii $p |- ( ph <-> ps ) $=
      wph wps wb wph wn wps wn wb con4bii.1 wph wps pm4.11 mpbir $.
      $( [21-May-1994] $)
  $}

  ${
    con4bid.1 $e |- ( ph -> ( -. ps <-> -. ch ) ) $.
    $( A contraposition deduction. $)
    con4bid $p |- ( ph -> ( ps <-> ch ) ) $=
      wph wps wn wch wn wb wps wch wb con4bid.1 wps wch pm4.11 sylibr $.
      $( [21-May-1994] $)
  $}

  $( Contraposition.  Theorem *4.12 of [WhiteheadRussell] p. 117. $)
  con2bi $p |- ( ( ph <-> -. ps ) <-> ( ps <-> -. ph ) ) $=
    wph wps wn wi wps wn wph wi wa wps wph wn wi wph wn wps wi wa wph wps wn wb
    wps wph wn wb wph wps wn wi wps wph wn wi wps wn wph wi wph wn wps wi wph
    wps bi2.03 wps wph bi2.15 anbi12i wph wps wn bi wps wph wn bi 3bitr4 $.
    $( [15-Apr-1995] $)

  ${
    con2bid.1 $e |- ( ph -> ( ps <-> -. ch ) ) $.
    $( A contraposition deduction. $)
    con2bid $p |- ( ph -> ( ch <-> -. ps ) ) $=
      wph wps wch wn wb wch wps wn wb con2bid.1 wch wps con2bi sylibr $.
      $( [15-Apr-1995] $)
  $}

  ${
    con1bid.1 $e |- ( ph -> ( -. ps <-> ch ) ) $.
    $( A contraposition deduction. $)
    con1bid $p |- ( ph -> ( -. ch <-> ps ) ) $=
      wph wps wch wn wph wch wps wph wps wn wch con1bid.1 bicomd con2bid bicomd
      $.
      $( [9-Oct-1999] $)
  $}

  ${
    bitrd.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    bitrd.2 $e |- ( ph -> ( ch <-> th ) ) $.
    $( Deduction form of ~ bitr . $)
    bitrd $p |- ( ph -> ( ps <-> th ) ) $=
      wph wps wth wph wps wch wth wph wps wch bitrd.1 biimpd bitrd.2 sylibd wph
      wth wch wps wph wch wth bitrd.2 biimprd bitrd.1 sylibrd impbid $.
      $( [5-Aug-1993] $)
  $}

  ${
    bitr2d.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    bitr2d.2 $e |- ( ph -> ( ch <-> th ) ) $.
    $( Deduction form of ~ bitr2 . $)
    bitr2d $p |- ( ph -> ( th <-> ps ) ) $=
      wph wps wth wph wps wch wth bitr2d.1 bitr2d.2 bitrd bicomd $.
      $( [11-Jun-2004] $) $( [9-Jun-2004] $)
  $}

  ${
    bitr3d.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    bitr3d.2 $e |- ( ph -> ( ps <-> th ) ) $.
    $( Deduction form of ~ bitr3 . $)
    bitr3d $p |- ( ph -> ( ch <-> th ) ) $=
      wph wch wps wth wph wps wch bitr3d.1 bicomd bitr3d.2 bitrd $.
      $( [5-Aug-1993] $)
  $}

  ${
    bitr4d.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    bitr4d.2 $e |- ( ph -> ( th <-> ch ) ) $.
    $( Deduction form of ~ bitr4 . $)
    bitr4d $p |- ( ph -> ( ps <-> th ) ) $=
      wph wps wch wth bitr4d.1 wph wth wch bitr4d.2 bicomd bitrd $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl5bb.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl5bb.2 $e |- ( th <-> ps ) $.
    $( A syllogism inference from two biconditionals. $)
    syl5bb $p |- ( ph -> ( th <-> ch ) ) $=
      wph wth wps wch wth wps wb wph syl5bb.2 a1i syl5bb.1 bitrd $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl5rbb.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl5rbb.2 $e |- ( th <-> ps ) $.
    $( A syllogism inference from two biconditionals. $)
    syl5rbb $p |- ( ph -> ( ch <-> th ) ) $=
      wph wth wch wph wps wch wth syl5rbb.1 syl5rbb.2 syl5bb bicomd $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl5bbr.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl5bbr.2 $e |- ( ps <-> th ) $.
    $( A syllogism inference from two biconditionals. $)
    syl5bbr $p |- ( ph -> ( th <-> ch ) ) $=
      wph wps wch wth syl5bbr.1 wps wth syl5bbr.2 bicomi syl5bb $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl5rbbr.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl5rbbr.2 $e |- ( ps <-> th ) $.
    $( A syllogism inference from two biconditionals. $)
    syl5rbbr $p |- ( ph -> ( ch <-> th ) ) $=
      wph wps wch wth syl5rbbr.1 wps wth syl5rbbr.2 bicomi syl5rbb $.
      $( [25-Nov-1994] $)
  $}

  ${
    syl6bb.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl6bb.2 $e |- ( ch <-> th ) $.
    $( A syllogism inference from two biconditionals. $)
    syl6bb $p |- ( ph -> ( ps <-> th ) ) $=
      wph wps wch wth syl6bb.1 wch wth wb wph syl6bb.2 a1i bitrd $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl6rbb.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl6rbb.2 $e |- ( ch <-> th ) $.
    $( A syllogism inference from two biconditionals. $)
    syl6rbb $p |- ( ph -> ( th <-> ps ) ) $=
      wph wps wth wph wps wch wth syl6rbb.1 syl6rbb.2 syl6bb bicomd $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl6bbr.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl6bbr.2 $e |- ( th <-> ch ) $.
    $( A syllogism inference from two biconditionals. $)
    syl6bbr $p |- ( ph -> ( ps <-> th ) ) $=
      wph wps wch wth syl6bbr.1 wth wch syl6bbr.2 bicomi syl6bb $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl6rbbr.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl6rbbr.2 $e |- ( th <-> ch ) $.
    $( A syllogism inference from two biconditionals. $)
    syl6rbbr $p |- ( ph -> ( th <-> ps ) ) $=
      wph wps wch wth syl6rbbr.1 wth wch syl6rbbr.2 bicomi syl6rbb $.
      $( [25-Nov-1994] $)
  $}

  ${
    sylan9bb.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    sylan9bb.2 $e |- ( th -> ( ch <-> ta ) ) $.
    $( Nested syllogism inference conjoining dissimilar antecedents. $)
    sylan9bb $p |- ( ( ph /\ th ) -> ( ps <-> ta ) ) $=
      wph wth wa wps wch wta wph wps wch wb wth sylan9bb.1 adantr wth wch wta
      wb wph sylan9bb.2 adantl bitrd $.
      $( [4-Mar-1995] $)
  $}

  ${
    sylan9bbr.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    sylan9bbr.2 $e |- ( th -> ( ch <-> ta ) ) $.
    $( Nested syllogism inference conjoining dissimilar antecedents. $)
    sylan9bbr $p |- ( ( th /\ ph ) -> ( ps <-> ta ) ) $=
      wph wth wps wta wb wph wps wch wth wta sylan9bbr.1 sylan9bbr.2 sylan9bb
      ancoms $.
      $( [4-Mar-1995] $)
  $}

  ${
    3imtr3d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    3imtr3d.2 $e |- ( ph -> ( ps <-> th ) ) $.
    3imtr3d.3 $e |- ( ph -> ( ch <-> ta ) ) $.
    $( More general version of ~ 3imtr3 .  Useful for converting
       conditional definitions in a formula. $)
    3imtr3d $p |- ( ph -> ( th -> ta ) ) $=
      wph wth wps wta 3imtr3d.2 wph wps wch wta 3imtr3d.1 3imtr3d.3 sylibd
      sylbird $.
      $( [8-Apr-1996] $)
  $}

  ${
    3imtr4d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    3imtr4d.2 $e |- ( ph -> ( th <-> ps ) ) $.
    3imtr4d.3 $e |- ( ph -> ( ta <-> ch ) ) $.
    $( More general version of ~ 3imtr4 .  Useful for converting
       conditional definitions in a formula. $)
    3imtr4d $p |- ( ph -> ( th -> ta ) ) $=
      wph wth wps wta 3imtr4d.2 wph wps wch wta 3imtr4d.1 3imtr4d.3 sylibrd
      sylbid $.
      $( [26-Oct-1995] $)
  $}

  ${
    3bitrd.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    3bitrd.2 $e |- ( ph -> ( ch <-> th ) ) $.
    3bitrd.3 $e |- ( ph -> ( th <-> ta ) ) $.
    $( Deduction from transitivity of biconditional. $)
    3bitrd $p |- ( ph -> ( ps <-> ta ) ) $=
      wph wps wth wta wph wps wch wth 3bitrd.1 3bitrd.2 bitrd 3bitrd.3 bitrd $.
      $( [13-Aug-1999] $)

    $( Deduction from transitivity of biconditional. $)
    3bitrrd $p |- ( ph -> ( ta <-> ps ) ) $=
      wph wth wta wps 3bitrd.3 wph wps wch wth 3bitrd.1 3bitrd.2 bitr2d bitr3d
      $.
      $( [11-Aug-2006] $) $( [4-Aug-2006] $)
  $}

  ${
    3bitr2d.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    3bitr2d.2 $e |- ( ph -> ( th <-> ch ) ) $.
    3bitr2d.3 $e |- ( ph -> ( th <-> ta ) ) $.
    $( Deduction from transitivity of biconditional. $)
    3bitr2d $p |- ( ph -> ( ps <-> ta ) ) $=
      wph wps wth wta wph wps wch wth 3bitr2d.1 3bitr2d.2 bitr4d 3bitr2d.3
      bitrd $.
      $( [11-Aug-2006] $) $( [4-Aug-2006] $)

    $( Deduction from transitivity of biconditional. $)
    3bitr2rd $p |- ( ph -> ( ta <-> ps ) ) $=
      wph wps wth wta wph wps wch wth 3bitr2d.1 3bitr2d.2 bitr4d 3bitr2d.3
      bitr2d $.
      $( [11-Aug-2006] $) $( [4-Aug-2006] $)
  $}

  ${
    3bitr3d.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    3bitr3d.2 $e |- ( ph -> ( ps <-> th ) ) $.
    3bitr3d.3 $e |- ( ph -> ( ch <-> ta ) ) $.
    $( Deduction from transitivity of biconditional.  Useful for converting
       conditional definitions in a formula. $)
    3bitr3d $p |- ( ph -> ( th <-> ta ) ) $=
      wph wth wch wta wph wps wth wch 3bitr3d.2 3bitr3d.1 bitr3d 3bitr3d.3
      bitrd $.
      $( [24-Apr-1996] $)

    $( Deduction from transitivity of biconditional. $)
    3bitr3rd $p |- ( ph -> ( ta <-> th ) ) $=
      wph wch wta wth 3bitr3d.3 wph wps wch wth 3bitr3d.1 3bitr3d.2 bitr3d
      bitr3d $.
      $( [11-Aug-2006] $) $( [4-Aug-2006] $)
  $}

  ${
    3bitr4d.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    3bitr4d.2 $e |- ( ph -> ( th <-> ps ) ) $.
    3bitr4d.3 $e |- ( ph -> ( ta <-> ch ) ) $.
    $( Deduction from transitivity of biconditional.  Useful for converting
       conditional definitions in a formula. $)
    3bitr4d $p |- ( ph -> ( th <-> ta ) ) $=
      wph wth wps wta 3bitr4d.2 wph wps wch wta 3bitr4d.1 3bitr4d.3 bitr4d
      bitrd $.
      $( [18-Oct-1995] $)

    $( Deduction from transitivity of biconditional. $)
    3bitr4rd $p |- ( ph -> ( ta <-> th ) ) $=
      wph wta wps wth wph wta wch wps 3bitr4d.3 3bitr4d.1 bitr4d 3bitr4d.2
      bitr4d $.
      $( [11-Aug-2006] $) $( [4-Aug-2006] $)
  $}

  ${
    3imtr3g.1 $e |- ( ph -> ( ps -> ch ) ) $.
    3imtr3g.2 $e |- ( ps <-> th ) $.
    3imtr3g.3 $e |- ( ch <-> ta ) $.
    $( More general version of ~ 3imtr3 .  Useful for converting
       definitions in a formula. $)
    3imtr3g $p |- ( ph -> ( th -> ta ) ) $=
      wph wth wta wph wps wa wch wph wth wa wta wph wps wch 3imtr3g.1 imp wps
      wth wph 3imtr3g.2 anbi2i 3imtr3g.3 3imtr3 ex $.
      $( [20-May-1996] $)
  $}

  ${
    3imtr4g.1 $e |- ( ph -> ( ps -> ch ) ) $.
    3imtr4g.2 $e |- ( th <-> ps ) $.
    3imtr4g.3 $e |- ( ta <-> ch ) $.
    $( More general version of ~ 3imtr4 .  Useful for converting
       definitions in a formula. $)
    3imtr4g $p |- ( ph -> ( th -> ta ) ) $=
      wph wps wch wth wta 3imtr4g.1 wth wps 3imtr4g.2 bicomi wta wch 3imtr4g.3
      bicomi 3imtr3g $.
      $( [20-May-1996] $)
  $}

  ${
    3bitr3g.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    3bitr3g.2 $e |- ( ps <-> th ) $.
    3bitr3g.3 $e |- ( ch <-> ta ) $.
    $( More general version of ~ 3bitr3 .  Useful for converting
       definitions in a formula. $)
    3bitr3g $p |- ( ph -> ( th <-> ta ) ) $=
      wph wth wch wta wph wps wch wth 3bitr3g.1 3bitr3g.2 syl5bbr 3bitr3g.3
      syl6bb $.
      $( [4-Jun-1995] $)
  $}

  ${
    3bitr4g.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    3bitr4g.2 $e |- ( th <-> ps ) $.
    3bitr4g.3 $e |- ( ta <-> ch ) $.
    $( More general version of ~ 3bitr4 .  Useful for converting
       definitions in a formula. $)
    3bitr4g $p |- ( ph -> ( th <-> ta ) ) $=
      wph wth wch wta wph wps wch wth 3bitr4g.1 3bitr4g.2 syl5bb 3bitr4g.3
      syl6bbr $.
      $( [5-Aug-1993] $)
  $}

  $( Theorem *3.47 of [WhiteheadRussell] p. 113.  It was proved by Leibniz, and
     it evidently pleased him enough to call it 'praeclarum theorema.' $)
  prth $p |- ( ( ( ph -> ps ) /\ ( ch -> th ) ) ->
               ( ( ph /\ ch ) -> ( ps /\ th ) ) ) $=
    wph wps wi wch wth wi wph wch wps wth wa wph wps wi wph wch wth wi wch wps
    wth wa wi wps wch wth wi wch wps wth wa wi wi wph wps wth wps wth wa wch
    wps wth pm3.2 imim2d imim2i com23 imp4b $.
    $( [12-Aug-1993] $)

  $( Theorem *3.48 of [WhiteheadRussell] p. 114. $)
  pm3.48 $p |- ( ( ( ph -> ps ) /\ ( ch -> th ) ) ->
               ( ( ph \/ ch ) -> ( ps \/ th ) ) ) $=
    wph wps wi wch wth wi wa wph wn wch wi wps wn wth wi wph wch wo wps wth wo
    wph wps wi wch wth wi wa wps wn wph wn wch wth wph wps wi wch wth wi wa wph
    wps wph wps wi wch wth wi pm3.26 con3d wph wps wi wch wth wi pm3.27 imim12d
    wph wch df-or wps wth df-or 3imtr4g $.
    $( [28-Jan-1997] $)

  ${
    anim12d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    anim12d.2 $e |- ( ph -> ( th -> ta ) ) $.
    $( Conjoin antecedents and consequents in a deduction. $)
    anim12d $p |- ( ph -> ( ( ps /\ th ) -> ( ch /\ ta ) ) ) $=
      wps wch wi wth wta wi wps wth wa wch wta wa wi wph wps wch wth wta prth
      anim12d.1 anim12d.2 sylanc $.
      $( [3-Apr-1994] $)
  $}

  ${
    anim12ii.1 $e |- ( ph -> ( ps -> ch ) ) $.
    anim12ii.2 $e |- ( th -> ( ps -> ta ) ) $.
    $( Conjoin antecedents and consequents in a deduction. $)
    anim12ii $p |- ( ( ph /\ th ) -> ( ps -> ( ch /\ ta ) ) ) $=
      wps wph wth wa wch wta wa wps wph wch wth wta wph wps wch anim12ii.1
      com12 wth wps wta anim12ii.2 com12 anim12d com12 $.
      $( [12-Nov-2007] $) $( [11-Nov-2007] $)
  $}

  ${
    anim1d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Add a conjunct to right of antecedent and consequent in a deduction. $)
    anim1d $p |- ( ph -> ( ( ps /\ th ) -> ( ch /\ th ) ) ) $=
      wph wps wch wth wth anim1d.1 wph wth idd anim12d $.
      $( [3-Apr-1994] $)

    $( Add a conjunct to left of antecedent and consequent in a deduction. $)
    anim2d $p |- ( ph -> ( ( th /\ ps ) -> ( th /\ ch ) ) ) $=
      wph wth wth wps wch wph wth idd anim1d.1 anim12d $.
      $( [5-Aug-1993] $)
  $}

  $( Theorem *3.45 (Fact) of [WhiteheadRussell] p. 113. $)
  pm3.45 $p |-  ( ( ph -> ps ) -> ( ( ph /\ ch ) -> ( ps /\ ch ) ) ) $=
    wph wps wi wph wps wch wph wps wi id anim1d $.
    $( [17-Jan-2005] $) $( [3-Jan-2005] $)

  ${
    $v et $. $( Greek eta $)
    im2an9.wet $f wff et $.
    im2an9.1 $e |- ( ph -> ( ps -> ch ) ) $.
    im2an9.2 $e |- ( th -> ( ta -> et ) ) $.

    $( Deduction joining nested implications to form implication of
       conjunctions. $)
    im2anan9 $p |- ( ( ph /\ th ) -> ( ( ps /\ ta ) -> ( ch /\ et ) ) ) $=
      wph wth wa wps wch wta im2an9.wet wph wps wch wi wth im2an9.1 adantr wth
      wta im2an9.wet wi wph im2an9.2 adantl anim12d $.
      $( [29-Feb-1996] $)

    $( Deduction joining nested implications to form implication of
       conjunctions. $)
    im2anan9r $p |- ( ( th /\ ph ) -> ( ( ps /\ ta ) -> ( ch /\ et ) ) ) $=
      wth wph wa wps wch wta im2an9.wet wph wps wch wi wth im2an9.1 adantl wth
      wta im2an9.wet wi wph im2an9.2 adantr anim12d $.
      $( [29-Feb-1996] $)

  $}

  ${
    orim12d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    orim12d.2 $e |- ( ph -> ( th -> ta ) ) $.
    $( Disjoin antecedents and consequents in a deduction. $)
    orim12d $p |- ( ph -> ( ( ps \/ th ) -> ( ch \/ ta ) ) ) $=
      wps wch wi wth wta wi wps wth wo wch wta wo wi wph wps wch wth wta pm3.48
      orim12d.1 orim12d.2 sylanc $.
      $( [10-May-1994] $)
  $}

  ${
    orim1d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Disjoin antecedents and consequents in a deduction. $)
    orim1d $p |- ( ph -> ( ( ps \/ th ) -> ( ch \/ th ) ) ) $=
      wph wps wch wth wth orim1d.1 wph wth idd orim12d $.
      $( [23-Apr-1995] $)

    $( Disjoin antecedents and consequents in a deduction. $)
    orim2d $p |- ( ph -> ( ( th \/ ps ) -> ( th \/ ch ) ) ) $=
      wph wth wth wps wch wph wth idd orim1d.1 orim12d $.
      $( [23-Apr-1995] $)
  $}

  $( Axiom *1.6 (Sum) of [WhiteheadRussell] p. 97. $)
  orim2 $p |-  ( ( ps -> ch ) -> ( ( ph \/ ps ) -> ( ph \/ ch ) ) ) $=
    wps wch wi wps wch wph wps wch wi id orim2d $.
    $( [16-May-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.38 of [WhiteheadRussell] p. 105. $)
  pm2.38 $p |-  ( ( ps -> ch ) -> ( ( ps \/ ph ) -> ( ch \/ ph ) ) ) $=
    wps wch wi wps wch wph wps wch wi id orim1d $.
    $( [6-Mar-2008] $) $( [6-Mar-2008] $)

  $( Theorem *2.36 of [WhiteheadRussell] p. 105. $)
  pm2.36 $p |-  ( ( ps -> ch ) -> ( ( ph \/ ps ) -> ( ch \/ ph ) ) ) $=
    wps wch wi wps wph wo wch wph wo wph wps wo wph wps wch pm2.38 wph wps
    pm1.4 syl5 $.
    $( [6-Mar-2008] $) $( [6-Mar-2008] $)

  $( Theorem *2.37 of [WhiteheadRussell] p. 105. $)
  pm2.37 $p |-  ( ( ps -> ch ) -> ( ( ps \/ ph ) -> ( ph \/ ch ) ) ) $=
    wps wch wi wps wph wo wch wph wo wph wch wo wph wps wch pm2.38 wch wph
    pm1.4 syl6 $.
    $( [6-Mar-2008] $) $( [6-Mar-2008] $)

  $( Theorem *2.73 of [WhiteheadRussell] p. 108. $)
  pm2.73 $p |-  ( ( ph -> ps ) -> ( ( ( ph \/ ps ) \/ ch ) ->
                ( ps \/ ch ) ) ) $=
    wph wps wi wph wps wo wps wch wph wps pm2.621 orim1d $.
    $( [29-Apr-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.74 of [WhiteheadRussell] p. 108. $)
  pm2.74 $p |-  ( ( ps -> ph ) -> ( ( ( ph \/ ps ) \/ ch ) ->
                ( ph \/ ch ) ) ) $=
    wps wph wph wps wo wch wo wph wch wo wi wps wn wph wps wo wph wch wps wph
    orel2 orim1d wph wph wch wo wph wps wo wch wo wph wch orc a1d ja $.
    $( [9-May-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.75 of [WhiteheadRussell] p. 108. $)
  pm2.75 $p |-  ( ( ph \/ ps ) ->
                ( ( ph \/ ( ps -> ch ) ) -> ( ph \/ ch ) ) ) $=
    wph wph wps wch wi wo wph wch wo wi wps wph wph wch wo wph wps wch wi wo
    wph wch orc a1d wps wps wch wi wch wph wps wch pm2.27 orim2d jaoi $.
    $( [14-May-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.76 of [WhiteheadRussell] p. 108. $)
  pm2.76 $p |-  ( ( ph \/ ( ps -> ch ) ) ->
                ( ( ph \/ ps ) -> ( ph \/ ch ) ) ) $=
    wph wps wo wph wps wch wi wo wph wch wo wph wps wch pm2.75 com12 $.
    $( [16-May-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.8 of [WhiteheadRussell] p. 108. $)
  pm2.8 $p |-  ( ( ps \/ ch ) -> ( ( -. ch \/ th ) -> ( ps \/ th ) ) ) $=
    wps wch wn wth wo wps wth wo wi wch wps wps wth wo wch wn wth wo wps wth
    orc a1d wch wch wn wps wth wch wps pm2.24 orim1d jaoi $.
    $( [16-May-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.81 of [WhiteheadRussell] p. 108. $)
  pm2.81 $p |-  ( ( ps -> ( ch -> th ) ) -> ( ( ph \/ ps ) ->
                ( ( ph \/ ch ) -> ( ph \/ th ) ) ) ) $=
    wps wch wth wi wi wph wps wo wph wch wth wi wo wph wch wo wph wth wo wi wph
    wps wch wth wi orim2 wph wch wth pm2.76 syl6 $.
    $( [17-May-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.82 of [WhiteheadRussell] p. 108. $)
  pm2.82 $p |-  ( ( ( ph \/ ps ) \/ ch ) -> ( ( ( ph \/ -. ch ) \/ th ) ->
                ( ( ph \/ ps ) \/ th ) ) ) $=
    wph wps wo wch wo wph wch wn wo wph wps wo wth wph wps wo wph wch wn wo wph
    wps wo wi wch wph wps wo wph wch wn wo ax-1 wch wch wn wps wph wch wps
    pm2.24 orim2d jaoi orim1d $.
    $( [18-May-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.85 of [WhiteheadRussell] p. 108. $)
  pm2.85 $p |-  ( ( ( ph \/ ps ) -> ( ph \/ ch ) ) ->
                ( ph \/ ( ps -> ch ) ) ) $=
    wph wps wo wph wch wo wi wph wps wn wo wph wch wo wo wph wps wch wi wo wph
    wps wo wph wch wo wi wph wps wo wn wph wch wo wo wph wps wn wo wph wch wo
    wo wph wps wo wph wch wo imor wph wps wo wn wph wps wn wo wph wch wo wph
    wps pm2.48 orim1i sylbi wph wps wch wi wo wph wps wn wch wo wo wph wps wn
    wo wph wch wo wo wps wch wi wps wn wch wo wph wps wch imor orbi2i wph wps
    wn wch orordi bitr2 sylib $.
    $( [9-Jan-2005] $) $( [3-Jan-2005] $)

  ${
    pm3.2ni.1 $e |- -. ph $.
    pm3.2ni.2 $e |- -. ps $.
    $( Infer negated disjunction of negated premises. $)
    pm3.2ni $p |- -. ( ph \/ ps ) $=
      wph wps wo wn wph wn wps wn wa wph wn wps wn pm3.2ni.1 pm3.2ni.2 pm3.2i
      wph wps ioran mpbir $.
      $( [4-Apr-1995] $)
  $}

  $( Absorption of redundant internal disjunct.  Compare Theorem *4.45
     of [WhiteheadRussell] p. 119. $)
  orabs $p |- ( ph <-> ( ( ph \/ ps ) /\ ph ) ) $=
    wph wph wps wo wph wa wph wph wps wo wph wps orc ancri wph wps wo wph
    pm3.27 impbi $.
    $( [5-Aug-1993] $)

  $( Absorb a disjunct into a conjunct.  (Contributed by Roy F. Longton
     23-Jun-2005.) $)
  oranabs $p |- ( ( ( ph \/ -. ps ) /\ ps ) <-> ( ph /\ ps ) ) $=
    wph wps wn wo wps wa wph wps wa wph wps wn wo wps wph wps wa wph wps wph
    wps wa wi wps wn wph wps pm3.2 wps wph wps wa pm2.21 jaoi imp wph wph wps
    wn wo wps wph wps wn orc anim1i impbi $.
    $( [24-Jun-2005] $) $( [23-Jun-2005] $)

  $( Distribution of implication over biconditional.  Theorem *5.74 of
     [WhiteheadRussell] p. 126. $)
  pm5.74 $p |- ( ( ph -> ( ps <-> ch ) ) <->
               ( ( ph -> ps ) <-> ( ph -> ch ) ) ) $=
    wph wps wch wb wi wph wps wi wph wch wi wb wph wps wch wb wi wph wps wi wph
    wch wi wps wch wb wps wch wph wps wch bi1 imim3i wps wch wb wch wps wph wps
    wch bi2 imim3i impbid wph wps wi wph wch wi wb wph wph wa wps wch wi wch
    wps wi wa wph wps wch wb wph wps wi wph wch wi wb wph wps wch wi wph wch
    wps wi wph wps wi wph wch wi wb wph wps wch wph wps wi wph wch wi bi1
    pm2.86d wph wps wi wph wch wi wb wph wch wps wph wps wi wph wch wi bi2
    pm2.86d anim12d wph pm4.24 wps wch bi 3imtr4g impbi $.
    $( [1-Aug-1994] $)

  ${
    pm5.74i.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    $( Distribution of implication over biconditional (inference rule). $)
    pm5.74i $p |- ( ( ph -> ps ) <-> ( ph -> ch ) ) $=
      wph wps wch wb wi wph wps wi wph wch wi wb pm5.74i.1 wph wps wch pm5.74
      mpbi $.
      $( [1-Aug-1994] $)
  $}

  ${
    pm5.74d.1 $e |- ( ph -> ( ps -> ( ch <-> th ) ) ) $.
    $( Distribution of implication over biconditional (deduction rule). $)
    pm5.74d $p |- ( ph -> ( ( ps -> ch ) <-> ( ps -> th ) ) ) $=
      wph wps wch wth wb wi wps wch wi wps wth wi wb pm5.74d.1 wps wch wth
      pm5.74 sylib $.
      $( [21-Mar-1996] $)
  $}

  ${
    pm5.74da.1 $e |- ( ( ph /\ ps ) -> ( ch <-> th ) ) $.
    $( Distribution of implication over biconditional (deduction rule). $)
    pm5.74da $p |- ( ph -> ( ( ps -> ch ) <-> ( ps -> th ) ) ) $=
      wph wps wch wth wph wps wch wth wb pm5.74da.1 ex pm5.74d $.
      $( [5-May-2007] $) $( [4-May-2007] $)
  $}

  ${
    pm5.74ri.1 $e |- ( ( ph -> ps ) <-> ( ph -> ch ) ) $.
    $( Distribution of implication over biconditional (reverse inference
       rule). $)
    pm5.74ri $p |- ( ph -> ( ps <-> ch ) ) $=
      wph wps wch wb wi wph wps wi wph wch wi wb pm5.74ri.1 wph wps wch pm5.74
      mpbir $.
      $( [1-Aug-1994] $)
  $}

  ${
    pm5.74rd.1 $e |- ( ph -> ( ( ps -> ch ) <-> ( ps -> th ) ) ) $.
    $( Distribution of implication over biconditional (deduction rule). $)
    pm5.74rd $p |- ( ph -> ( ps -> ( ch <-> th ) ) ) $=
      wph wps wch wi wps wth wi wb wps wch wth wb wi pm5.74rd.1 wps wch wth
      pm5.74 sylibr $.
      $( [19-Mar-1997] $)
  $}

  ${
    mpbidi.min $e |- ( th -> ( ph -> ps ) ) $.
    mpbidi.maj $e |- ( ph -> ( ps <-> ch ) ) $.
    $( A deduction from a biconditional, related to modus ponens. $)
    mpbidi $p |- ( th -> ( ph -> ch ) ) $=
      wth wph wps wi wph wch wi mpbidi.min wph wps wch mpbidi.maj pm5.74i sylib
      $.
      $( [9-Aug-1994] $)
  $}

  $( Implication in terms of implication and biconditional. $)
  ibib $p |- ( ( ph -> ps ) <-> ( ph -> ( ph <-> ps ) ) ) $=
    wph wps wph wps wb wph wps wph wps wb wph wps wph wps wb wph wps wa wph wps
    wph wps pm3.4 wph wps wa wph wps wph wps pm3.26 a1d impbid ex wph wps wb
    wph wps wph wps bi1 com12 impbid pm5.74i $.
    $( [31-Mar-1994] $)

  $( Implication in terms of implication and biconditional. $)
  ibibr $p |- ( ( ph -> ps ) <-> ( ph -> ( ps <-> ph ) ) ) $=
    wph wps wi wph wph wps wb wi wph wps wph wb wi wph wps ibib wph wps wb wps
    wph wb wph wph wps bicom imbi2i bitr $.
    $( [6-Jun-2005] $) $( [29-Apr-2005] $)

  ${
    ibi.1 $e |- ( ph -> ( ph <-> ps ) ) $.
    $( Inference that converts a biconditional implied by one of its arguments,
       into an implication. $)
    ibi $p |- ( ph -> ps ) $=
      wph wps wph wph wps ibi.1 biimpd pm2.43i $.
      $( [17-Oct-2003] $) $( [17-Oct-2003] $)
  $}

  ${
    ibir.1 $e |- ( ph -> ( ps <-> ph ) ) $.
    $( Inference that converts a biconditional implied by one of its arguments,
       into an implication. $)
    ibir $p |- ( ph -> ps ) $=
      wph wps wph wps wph ibir.1 bicomd ibi $.
      $( [28-Jul-2004] $) $( [22-Jul-2004] $)
  $}

  ${
    ibd.1 $e |- ( ph -> ( ps -> ( ps <-> ch ) ) ) $.
    $( Deduction that converts a biconditional implied by one of its arguments,
       into an implication. $)
    ibd $p |- ( ph -> ( ps -> ch ) ) $=
      wph wps wps wch wb wi wps wch wi ibd.1 wps wch ibib sylibr $.
      $( [27-Jun-2004] $) $( [26-Jun-2004] $)
  $}

  $( Theorem *5.501 of [WhiteheadRussell] p. 125. $)
  pm5.501 $p |-  ( ph -> ( ps <-> ( ph <-> ps ) ) ) $=
    wph wps wph wps wb wph wps ibib pm5.74ri $.
    $( [1-Feb-2005] $) $( [3-Jan-2005] $)

  $( Distributive law for disjunction.  Theorem *4.41 of [WhiteheadRussell]
     p. 119. $)
  ordi $p |- ( ( ph \/ ( ps /\ ch ) ) <-> ( ( ph \/ ps ) /\ ( ph \/ ch ) ) ) $=
    wph wps wch wa wo wph wps wo wph wch wo wa wph wps wch wa wo wph wps wo wph
    wch wo wps wch wa wps wph wps wch pm3.26 orim2i wps wch wa wch wph wps wch
    pm3.27 orim2i jca wph wps wo wph wch wo wph wps wch wa wo wph wps wo wph wn
    wps wi wph wch wo wph wps wch wa wo wi wph wps df-or wph wn wps wi wph wn
    wch wi wph wn wps wch wa wi wph wch wo wph wps wch wa wo wph wn wps wch
    pm3.43i wph wch df-or wph wps wch wa df-or 3imtr4g sylbi imp impbi $.
    $( [5-Aug-1993] $)

  $( Distributive law for disjunction. $)
  ordir $p |- ( ( ( ph /\ ps ) \/ ch ) <->
              ( ( ph \/ ch ) /\ ( ps \/ ch ) ) ) $=
    wch wph wps wa wo wch wph wo wch wps wo wa wph wps wa wch wo wph wch wo wps
    wch wo wa wch wph wps ordi wph wps wa wch orcom wph wch wo wch wph wo wps
    wch wo wch wps wo wph wch orcom wps wch orcom anbi12i 3bitr4 $.
    $( [12-Aug-1994] $)

  $( Distributive law for implication over conjunction.  Compare Theorem
     *4.76 of [WhiteheadRussell] p. 121. $)
  jcab $p |- ( ( ph -> ( ps /\ ch ) ) <->
                 ( ( ph -> ps ) /\ ( ph -> ch ) ) ) $=
    wph wn wps wch wa wo wph wn wps wo wph wn wch wo wa wph wps wch wa wi wph
    wps wi wph wch wi wa wph wn wps wch ordi wph wps wch wa imor wph wps wi wph
    wn wps wo wph wch wi wph wn wch wo wph wps imor wph wch imor anbi12i 3bitr4
    $.
    $( [3-Apr-1994] $)

  $( Theorem *4.76 of [WhiteheadRussell] p. 121. $)
  pm4.76 $p |-  ( ( ( ph -> ps ) /\ ( ph -> ch ) ) <->
                ( ph -> ( ps /\ ch ) ) ) $=
    wph wps wch wa wi wph wps wi wph wch wi wa wph wps wch jcab bicomi $.
    $( [22-May-2005] $) $( [3-Jan-2005] $)

  ${
    jcad.1 $e |- ( ph -> ( ps -> ch ) ) $.
    jcad.2 $e |- ( ph -> ( ps -> th ) ) $.
    $( Deduction conjoining the consequents of two implications. $)
    jcad $p |- ( ph -> ( ps -> ( ch /\ th ) ) ) $=
      wph wps wch wth wa wph wps wa wch wth wph wps wch jcad.1 imp wph wps wth
      jcad.2 imp jca ex $.
      $( [5-Aug-1993] $)
  $}

  ${
    jctild.1 $e |- ( ph -> ( ps -> ch ) ) $.
    jctild.2 $e |- ( ph -> th ) $.
    $( Deduction conjoining a theorem to left of consequent in an
       implication. $)
    jctild $p |- ( ph -> ( ps -> ( th /\ ch ) ) ) $=
      wph wps wth wch wph wth wps jctild.2 a1d jctild.1 jcad $.
      $( [22-Apr-2005] $) $( [21-Apr-2005] $)
  $}

  ${
    jctird.1 $e |- ( ph -> ( ps -> ch ) ) $.
    jctird.2 $e |- ( ph -> th ) $.
    $( Deduction conjoining a theorem to right of consequent in an
       implication. $)
    jctird $p |- ( ph -> ( ps -> ( ch /\ th ) ) ) $=
      wph wps wch wth jctird.1 wph wth wps jctird.2 a1d jcad $.
      $( [22-Apr-2005] $) $( [21-Apr-2005] $)
  $}

  $( Theorem *3.43 (Comp) of [WhiteheadRussell] p. 113. $)
  pm3.43 $p |-  ( ( ( ph -> ps ) /\ ( ph -> ch ) ) ->
                ( ph -> ( ps /\ ch ) ) ) $=
    wph wps wch wa wi wph wps wi wph wch wi wa wph wps wch jcab biimpr $.
    $( [27-May-2005] $) $( [3-Jan-2005] $)

  $( Distributive law for conjunction.  Theorem *4.4 of [WhiteheadRussell]
     p. 118. $)
  andi $p |- ( ( ph /\ ( ps \/ ch ) ) <-> ( ( ph /\ ps ) \/ ( ph /\ ch ) ) ) $=
    wph wn wps wch wo wn wo wn wph wps wa wn wph wch wa wn wa wn wph wps wch wo
    wa wph wps wa wph wch wa wo wph wn wps wch wo wn wo wph wps wa wn wph wch
    wa wn wa wph wn wps wn wch wn wa wo wph wn wps wn wo wph wn wch wn wo wa
    wph wn wps wch wo wn wo wph wps wa wn wph wch wa wn wa wph wn wps wn wch wn
    ordi wps wch wo wn wps wn wch wn wa wph wn wps wch ioran orbi2i wph wps wa
    wn wph wn wps wn wo wph wch wa wn wph wn wch wn wo wph wps ianor wph wch
    ianor anbi12i 3bitr4 negbii wph wps wch wo anor wph wps wa wph wch wa oran
    3bitr4 $.
    $( [5-Aug-1993] $)

  $( Distributive law for conjunction. $)
  andir $p |- ( ( ( ph \/ ps ) /\ ch ) <->
              ( ( ph /\ ch ) \/ ( ps /\ ch ) ) ) $=
    wch wph wps wo wa wch wph wa wch wps wa wo wph wps wo wch wa wph wch wa wps
    wch wa wo wch wph wps andi wph wps wo wch ancom wph wch wa wch wph wa wps
    wch wa wch wps wa wph wch ancom wps wch ancom orbi12i 3bitr4 $.
    $( [12-Aug-1994] $)

  $( Double distributive law for disjunction. $)
  orddi $p |- ( ( ( ph /\ ps ) \/ ( ch /\ th ) ) <->
              ( ( ( ph \/ ch ) /\ ( ph \/ th ) ) /\
              ( ( ps \/ ch ) /\ ( ps \/ th ) ) ) ) $=
    wph wps wa wch wth wa wo wph wch wth wa wo wps wch wth wa wo wa wph wch wo
    wph wth wo wa wps wch wo wps wth wo wa wa wph wps wch wth wa ordir wph wch
    wth wa wo wph wch wo wph wth wo wa wps wch wth wa wo wps wch wo wps wth wo
    wa wph wch wth ordi wps wch wth ordi anbi12i bitr $.
    $( [12-Aug-1994] $)

  $( Double distributive law for conjunction. $)
  anddi $p |- ( ( ( ph \/ ps ) /\ ( ch \/ th ) ) <->
              ( ( ( ph /\ ch ) \/ ( ph /\ th ) ) \/
              ( ( ps /\ ch ) \/ ( ps /\ th ) ) ) ) $=
    wph wps wo wch wth wo wa wph wch wth wo wa wps wch wth wo wa wo wph wch wa
    wph wth wa wo wps wch wa wps wth wa wo wo wph wps wch wth wo andir wph wch
    wth wo wa wph wch wa wph wth wa wo wps wch wth wo wa wps wch wa wps wth wa
    wo wph wch wth andi wps wch wth andi orbi12i bitr $.
    $( [12-Aug-1994] $)

  $( Prove formula-building rules for the biconditional connective. $)

  ${
    bibi.a $e |- ( ph <-> ps ) $.

    $( Inference adding a biconditional to the left in an equivalence. $)
    bibi2i $p |- ( ( ch <-> ph ) <-> ( ch <-> ps ) ) $=
      wch wph wb wch wph wi wph wch wi wa wch wph wi wps wch wi wa wch wps wb
      wch wph bi wph wch wi wps wch wi wch wph wi wph wps wch bibi.a imbi1i
      anbi2i wch wph wi wps wch wi wa wch wps wi wps wch wi wa wch wps wb wch
      wph wi wch wps wi wps wch wi wph wps wch bibi.a imbi2i anbi1i wch wps bi
      bitr4 3bitr $.
      $( [5-Aug-1993] $)

    $( Inference adding a biconditional to the right in an equivalence. $)
    bibi1i $p |- ( ( ph <-> ch ) <-> ( ps <-> ch ) ) $=
      wph wch wb wch wph wb wch wps wb wps wch wb wph wch bicom wph wps wch
      bibi.a bibi2i wch wps bicom 3bitr $.
      $( [5-Aug-1993] $)

    ${
      bibi12.2 $e |- ( ch <-> th ) $.
      $( The equivalence of two equivalences. $)
      bibi12i $p |- ( ( ph <-> ch ) <-> ( ps <-> th ) ) $=
        wph wch wb wph wth wb wps wth wb wch wth wph bibi12.2 bibi2i wph wps
        wth bibi.a bibi1i bitr $.
        $( [5-Aug-1993] $)
    $}
  $}

  ${
    bid.1 $e |- ( ph -> ( ps <-> ch ) ) $.

    $( Deduction negating both sides of a logical equivalence. $)
    negbid $p |- ( ph -> ( -. ps <-> -. ch ) ) $=
      wph wps wch wb wps wn wch wn wb bid.1 wps wch pm4.11 sylib $.
      $( [21-May-1994] $)

    $( Deduction adding an antecedent to both sides of a logical
       equivalence. $)
    imbi2d $p |- ( ph -> ( ( th -> ps ) <-> ( th -> ch ) ) ) $=
      wph wth wps wch wph wps wch wb wth bid.1 a1d pm5.74d $.
      $( [5-Aug-1993] $)

    $( Deduction adding a consequent to both sides of a logical equivalence. $)
    imbi1d $p |- ( ph -> ( ( ps -> th ) <-> ( ch -> th ) ) ) $=
      wph wth wn wps wn wi wth wn wch wn wi wps wth wi wch wth wi wph wps wn
      wch wn wth wn wph wps wch bid.1 negbid imbi2d wps wth pm4.1 wch wth pm4.1
      3bitr4g $.
      $( [5-Aug-1993] $)

    $( Deduction adding a left disjunct to both sides of a logical
       equivalence. $)
    orbi2d $p |- ( ph -> ( ( th \/ ps ) <-> ( th \/ ch ) ) ) $=
      wph wth wn wps wi wth wn wch wi wth wps wo wth wch wo wph wps wch wth wn
      bid.1 imbi2d wth wps df-or wth wch df-or 3bitr4g $.
      $( [5-Aug-1993] $)

    $( Deduction adding a right disjunct to both sides of a logical
       equivalence. $)
    orbi1d $p |- ( ph -> ( ( ps \/ th ) <-> ( ch \/ th ) ) ) $=
      wph wth wps wo wth wch wo wps wth wo wch wth wo wph wps wch wth bid.1
      orbi2d wps wth orcom wch wth orcom 3bitr4g $.
      $( [5-Aug-1993] $)

    $( Deduction adding a left conjunct to both sides of a logical
       equivalence. $)
    anbi2d $p |- ( ph -> ( ( th /\ ps ) <-> ( th /\ ch ) ) ) $=
      wph wth wps wa wth wch wa wph wps wch wth wph wps wch bid.1 biimpd anim2d
      wph wch wps wth wph wps wch bid.1 biimprd anim2d impbid $.
      $( [5-Aug-1993] $)

    $( Deduction adding a right conjunct to both sides of a logical
       equivalence. $)
    anbi1d $p |- ( ph -> ( ( ps /\ th ) <-> ( ch /\ th ) ) ) $=
      wph wth wps wa wth wch wa wps wth wa wch wth wa wph wps wch wth bid.1
      anbi2d wps wth ancom wch wth ancom 3bitr4g $.
      $( [5-Aug-1993] $)

    $( Deduction adding a biconditional to the left in an equivalence. $)
    bibi2d $p |- ( ph -> ( ( th <-> ps ) <-> ( th <-> ch ) ) ) $=
      wph wth wps wi wps wth wi wa wth wch wi wch wth wi wa wth wps wb wth wch
      wb wph wth wps wi wps wth wi wa wth wch wi wps wth wi wa wth wch wi wch
      wth wi wa wph wth wps wi wth wch wi wps wth wi wph wps wch wth bid.1
      imbi2d anbi1d wph wps wth wi wch wth wi wth wch wi wph wps wch wth bid.1
      imbi1d anbi2d bitrd wth wps bi wth wch bi 3bitr4g $.
      $( [5-Aug-1993] $)

    $( Deduction adding a biconditional to the right in an equivalence. $)
    bibi1d $p |- ( ph -> ( ( ps <-> th ) <-> ( ch <-> th ) ) ) $=
      wph wth wps wb wth wch wb wps wth wb wch wth wb wph wps wch wth bid.1
      bibi2d wps wth bicom wch wth bicom 3bitr4g $.
      $( [5-Aug-1993] $)

  $}

  $( Theorem *4.37 of [WhiteheadRussell] p. 118. $)
  orbi1 $p |-  ( ( ph <-> ps ) -> ( ( ph \/ ch ) <-> ( ps \/ ch ) ) ) $=
    wph wps wb wph wps wch wph wps wb id orbi1d $.
    $( [12-Jun-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.36 of [WhiteheadRussell] p. 118. $)
  anbi1 $p |-  ( ( ph <-> ps ) -> ( ( ph /\ ch ) <-> ( ps /\ ch ) ) ) $=
    wph wps wb wph wps wch wph wps wb id anbi1d $.
    $( [15-Jun-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.22 of [WhiteheadRussell] p. 117. $)
  pm4.22 $p |-  ( ( ( ph <-> ps ) /\ ( ps <-> ch ) ) -> ( ph <-> ch ) ) $=
    wph wps wb wph wch wb wps wch wb wph wps wb wph wps wch wph wps wb id
    bibi1d biimpar $.
    $( [30-May-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.84 of [WhiteheadRussell] p. 122. $)
  imbi1 $p |-  ( ( ph <-> ps ) -> ( ( ph -> ch ) <-> ( ps -> ch ) ) ) $=
    wph wps wb wph wps wch wph wps wb id imbi1d $.
    $( [9-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.85 of [WhiteheadRussell] p. 122. $)
  imbi2 $p |-  ( ( ph <-> ps ) -> ( ( ch -> ph ) <-> ( ch -> ps ) ) ) $=
    wph wps wb wch wph wps wph wps wb wch ax-1 pm5.74d $.
    $( [9-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.86 of [WhiteheadRussell] p. 122. $)
  bibi1 $p |-  ( ( ph <-> ps ) -> ( ( ph <-> ch ) <-> ( ps <-> ch ) ) ) $=
    wph wps wb wph wps wch wph wps wb id bibi1d $.
    $( [15-Jun-2005] $) $( [3-Jan-2005] $)

  ${
    bi12d.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    bi12d.2 $e |- ( ph -> ( th <-> ta ) ) $.
    $( Deduction joining two equivalences to form equivalence of
       implications. $)
    imbi12d $p |- ( ph -> ( ( ps -> th ) <-> ( ch -> ta ) ) ) $=
      wph wps wth wi wch wth wi wch wta wi wph wps wch wth bi12d.1 imbi1d wph
      wth wta wch bi12d.2 imbi2d bitrd $.
      $( [5-Aug-1993] $)

    $( Deduction joining two equivalences to form equivalence of
       disjunctions. $)
    orbi12d $p |- ( ph -> ( ( ps \/ th ) <-> ( ch \/ ta ) ) ) $=
      wph wps wth wo wch wth wo wch wta wo wph wps wch wth bi12d.1 orbi1d wph
      wth wta wch bi12d.2 orbi2d bitrd $.
      $( [5-Aug-1993] $)

    $( Deduction joining two equivalences to form equivalence of
       conjunctions. $)
    anbi12d $p |- ( ph -> ( ( ps /\ th ) <-> ( ch /\ ta ) ) ) $=
      wph wps wth wa wch wth wa wch wta wa wph wps wch wth bi12d.1 anbi1d wph
      wth wta wch bi12d.2 anbi2d bitrd $.
      $( [5-Aug-1993] $)

    $( Deduction joining two equivalences to form equivalence of
       biconditionals. $)
    bibi12d $p |- ( ph -> ( ( ps <-> th ) <-> ( ch <-> ta ) ) ) $=
      wph wps wth wb wch wth wb wch wta wb wph wps wch wth bi12d.1 bibi1d wph
      wth wta wch bi12d.2 bibi2d bitrd $.
      $( [5-Aug-1993] $)

  $}

  $( Theorem *4.39 of [WhiteheadRussell] p. 118. $)
  pm4.39 $p |-  ( ( ( ph <-> ch ) /\ ( ps <-> th ) ) ->
                ( ( ph \/ ps ) <-> ( ch \/ th ) ) ) $=
    wph wch wb wps wth wb wa wph wch wps wth wph wch wb wps wth wb pm3.26 wph
    wch wb wps wth wb pm3.27 orbi12d $.
    $( [30-May-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.38 of [WhiteheadRussell] p. 118. $)
  pm4.38 $p |-  ( ( ( ph <-> ch ) /\ ( ps <-> th ) ) ->
                ( ( ph /\ ps ) <-> ( ch /\ th ) ) ) $=
    wph wch wb wps wth wb wa wph wch wps wth wph wch wb wps wth wb pm3.26 wph
    wch wb wps wth wb pm3.27 anbi12d $.
    $( [30-May-2005] $) $( [3-Jan-2005] $)

  ${
    $v et $. $( Greek eta $)
    bi2an9.wet $f wff et $.
    bi2an9.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    bi2an9.2 $e |- ( th -> ( ta <-> et ) ) $.

    $( Deduction joining two equivalences to form equivalence of
       conjunctions. $)
    bi2anan9 $p |- ( ( ph /\ th ) -> ( ( ps /\ ta ) <-> ( ch /\ et ) ) ) $=
      wph wps wta wa wch wta wa wth wch bi2an9.wet wa wph wps wch wta bi2an9.1
      anbi1d wth wta bi2an9.wet wch bi2an9.2 anbi2d sylan9bb $.
      $( [31-Jul-1995] $)

    $( Deduction joining two equivalences to form equivalence of
       conjunctions. $)
    bi2anan9r $p |- ( ( th /\ ph ) -> ( ( ps /\ ta ) <-> ( ch /\ et ) ) ) $=
      wph wth wps wta wa wch bi2an9.wet wa wb wph wps wch wth wta bi2an9.wet
      bi2an9.1 bi2an9.2 bi2anan9 ancoms $.
      $( [19-Feb-1996] $)

    $( Deduction joining two biconditionals with different antecedents. $)
    bi2bian9 $p |- ( ( ph /\ th ) -> ( ( ps <-> ta ) <-> ( ch <-> et ) ) ) $=
      wph wth wa wps wch wta bi2an9.wet wph wps wch wb wth bi2an9.1 adantr wth
      wta bi2an9.wet wb wph bi2an9.2 adantl bibi12d $.
      $( [14-May-2004] $) $( [12-May-2004] $)
  $}

  $( Implication in terms of biconditional and conjunction.  Theorem *4.71 of
     [WhiteheadRussell] p. 120. $)
  pm4.71 $p |- ( ( ph -> ps ) <-> ( ph <-> ( ph /\ ps ) ) ) $=
    wph wps wi wph wph wps wa wb wph wps wi wph wph wps wa wph wps ancl wph wps
    pm3.26 impbid1 wph wph wps wa wb wph wph wps wa wps wph wph wps wa bi1 wph
    wps pm3.27 syl6 impbi $.
    $( [5-Aug-1993] $)

  $( Implication in terms of biconditional and conjunction.  Theorem *4.71 of
     [WhiteheadRussell] p. 120 (with conjunct reversed). $)
  pm4.71r $p |- ( ( ph -> ps ) <-> ( ph <-> ( ps /\ ph ) ) ) $=
    wph wps wi wph wph wps wa wb wph wps wph wa wb wph wps pm4.71 wph wps wa
    wps wph wa wph wph wps ancom bibi2i bitr $.
    $( [25-Jul-1999] $)

  ${
    pm4.71i.1 $e |- ( ph -> ps ) $.
    $( Inference converting an implication to a biconditional with conjunction.
       Inference from Theorem *4.71 of [WhiteheadRussell] p. 120. $)
    pm4.71i $p |- ( ph <-> ( ph /\ ps ) ) $=
      wph wps wi wph wph wps wa wb pm4.71i.1 wph wps pm4.71 mpbi $.
      $( [6-Jan-2004] $) $( [4-Jan-2004] $)
  $}

  ${
    pm4.71ri.1 $e |- ( ph -> ps ) $.
    $( Inference converting an implication to a biconditional with conjunction.
       Inference from Theorem *4.71 of [WhiteheadRussell] p. 120 (with
       conjunct reversed). $)
    pm4.71ri $p |- ( ph <-> ( ps /\ ph ) ) $=
      wph wps wi wph wps wph wa wb pm4.71ri.1 wph wps pm4.71r mpbi $.
      $( [1-Dec-2003] $) $( [1-Dec-2003] $)
  $}

  ${
    pm4.71rd.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction converting an implication to a biconditional with conjunction.
       Deduction from Theorem *4.71 of [WhiteheadRussell] p. 120. $)
    pm4.71rd $p |- ( ph -> ( ps <-> ( ch /\ ps ) ) ) $=
      wph wps wch wi wps wch wps wa wb pm4.71rd.1 wps wch pm4.71r sylib $.
      $( [12-Feb-2005] $) $( [10-Feb-2005] $)
  $}

  $( Theorem *4.45 of [WhiteheadRussell] p. 119. $)
  pm4.45 $p |-  ( ph <-> ( ph /\ ( ph \/ ps ) ) ) $=
    wph wph wps wo wph wps orc pm4.71i $.
    $( [30-May-2005] $) $( [3-Jan-2005] $)

  $( Implication in terms of biconditional and disjunction.  Theorem *4.72 of
     [WhiteheadRussell] p. 121. $)
  pm4.72 $p |- ( ( ph -> ps ) <-> ( ps <-> ( ph \/ ps ) ) ) $=
    wph wps wi wps wph wps wo wb wph wps wi wps wph wps wo wps wph olc wph wps
    pm2.621 impbid2 wps wph wps wo wb wph wps wo wps wi wph wps wi wps wph wps
    wo bi2 wph wps pm2.67 syl impbi $.
    $( [30-Aug-1993] $)

  $( Introduction of antecedent as conjunct.  Theorem *4.73 of
     [WhiteheadRussell] p. 121. $)
  iba $p |- ( ph -> ( ps <-> ( ps /\ ph ) ) ) $=
    wph wps wps wph wa wph wps ancrb pm5.74ri $.
    $( [30-Mar-1994] $)

  $( Introduction of antecedent as conjunct. $)
  ibar $p |- ( ph -> ( ps <-> ( ph /\ ps ) ) ) $=
    wph wps wph wps wa wph wps anclb pm5.74ri $.
    $( [5-Dec-1995] $)

  $( Distribution of implication over biconditional.  Theorem *5.32 of
     [WhiteheadRussell] p. 125. $)
  pm5.32 $p |- ( ( ph -> ( ps <-> ch ) ) <->
               ( ( ph /\ ps ) <-> ( ph /\ ch ) ) ) $=
    wph wps wch wb wi wph wps wn wi wn wph wch wn wi wn wb wph wps wa wph wch
    wa wb wph wps wch wb wi wph wps wn wch wn wb wi wph wps wn wi wph wch wn wi
    wb wph wps wn wi wn wph wch wn wi wn wb wps wch wb wps wn wch wn wb wph wps
    wch pm4.11 imbi2i wph wps wn wch wn pm5.74 wph wps wn wi wph wch wn wi
    pm4.11 3bitr wph wps wa wph wps wn wi wn wph wch wa wph wch wn wi wn wph
    wps df-an wph wch df-an bibi12i bitr4 $.
    $( [1-Aug-1994] $)

  ${
    pm5.32i.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    $( Distribution of implication over biconditional (inference rule). $)
    pm5.32i $p |- ( ( ph /\ ps ) <-> ( ph /\ ch ) ) $=
      wph wps wch wb wi wph wps wa wph wch wa wb pm5.32i.1 wph wps wch pm5.32
      mpbi $.
      $( [1-Aug-1994] $)

    $( Distribution of implication over biconditional (inference rule). $)
    pm5.32ri $p |- ( ( ps /\ ph ) <-> ( ch /\ ph ) ) $=
      wph wps wa wph wch wa wps wph wa wch wph wa wph wps wch pm5.32i.1 pm5.32i
      wps wph ancom wch wph ancom 3bitr4 $.
      $( [12-Mar-1995] $)
  $}

  ${
    pm5.32d.1 $e |- ( ph -> ( ps -> ( ch <-> th ) ) ) $.
    $( Distribution of implication over biconditional (deduction rule). $)
    pm5.32d $p |- ( ph -> ( ( ps /\ ch ) <-> ( ps /\ th ) ) ) $=
      wph wps wch wth wb wi wps wch wa wps wth wa wb pm5.32d.1 wps wch wth
      pm5.32 sylib $.
      $( [29-Oct-1996] $)

    $( Distribution of implication over biconditional (deduction rule). $)
    pm5.32rd $p |- ( ph -> ( ( ch /\ ps ) <-> ( th /\ ps ) ) ) $=
      wph wps wch wa wps wth wa wch wps wa wth wps wa wph wps wch wth pm5.32d.1
      pm5.32d wch wps ancom wth wps ancom 3bitr4g $.
      $( [1-Jan-2005] $) $( [25-Dec-2004] $)
  $}

  ${
    pm5.32da.1 $e |- ( ( ph /\ ps ) -> ( ch <-> th ) ) $.
    $( Distribution of implication over biconditional (deduction rule). $)
    pm5.32da $p |- ( ph -> ( ( ps /\ ch ) <-> ( ps /\ th ) ) ) $=
      wph wps wch wth wph wps wch wth wb pm5.32da.1 ex pm5.32d $.
      $( [10-Dec-2006] $) $( [9-Dec-2006] $)
  $}

  $( Theorem *5.33 of [WhiteheadRussell] p. 125. $)
  pm5.33 $p |-  ( ( ph /\ ( ps -> ch ) ) <->
                ( ph /\ ( ( ph /\ ps ) -> ch ) ) ) $=
    wph wps wch wi wph wps wa wch wi wph wps wph wps wa wch wph wps ibar imbi1d
    pm5.32i $.
    $( [31-May-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.36 of [WhiteheadRussell] p. 125. $)
  pm5.36 $p |-  ( ( ph /\ ( ph <-> ps ) ) <-> ( ps /\ ( ph <-> ps ) ) ) $=
    wph wps wb wph wps wph wps wb id pm5.32ri $.
    $( [31-May-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.42 of [WhiteheadRussell] p. 125. $)
  pm5.42 $p |-  ( ( ph -> ( ps -> ch ) ) <->
                ( ph -> ( ps -> ( ph /\ ch ) ) ) ) $=
    wph wps wch wi wps wph wch wa wi wph wch wph wch wa wps wph wch ibar imbi2d
    pm5.74i $.
    $( [3-Jun-2005] $) $( [3-Jan-2005] $)

  $( Absorption of disjunction into equivalence. $)
  oibabs $p |- ( ( ( ph \/ ps ) -> ( ph <-> ps ) ) <-> ( ph <-> ps ) ) $=
    wph wps wo wph wps wb wi wph wps wb wph wps wo wph wps wb wi wph wps wph
    wps wo wph wps wb wi wph wps wph wph wps wo wph wps wb wph wps orc imim1i
    ibd wph wps wo wph wps wb wi wps wph wps wb wi wps wph wi wps wph wps wo
    wph wps wb wps wph olc imim1i wps wph ibibr sylibr impbid wph wps wb wph
    wps wo ax-1 impbi $.
    $( [29-Jan-2008] $)  $( [6-Aug-1995] $)

  $( Law of excluded middle, also called the principle of _tertium non datur_.
     Theorem *2.11 of [WhiteheadRussell] p. 101.  It says that something is
     either true or not true; there are no in-between values of truth.  This is
     an essential distinction of our classical logic and is not a theorem of
     intuitionistic logic. $)
  exmid $p |- ( ph \/ -. ph ) $=
    wph wph wn wph wn id orri $.
    $( [5-Aug-1993] $)

  $( Theorem *2.1 of [WhiteheadRussell] p. 101. $)
  pm2.1 $p |-  ( -. ph \/ ph ) $=
    wph wn wph wph nega orri $.
    $( [7-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.13 of [WhiteheadRussell] p. 101. $)
  pm2.13 $p |-  ( ph \/ -. -. -. ph ) $=
    wph wph wn wn wn wph wn negb orri $.
    $( [4-Jun-2005] $) $( [3-Jan-2005] $)

  $( Law of noncontradiction.  Theorem *3.24 of [WhiteheadRussell] p. 111
     (who call it the "law of contradiction"). $)
  pm3.24 $p |- -. ( ph /\ -. ph ) $=
    wph wph wn wa wn wph wn wph wn wn wo wph wn exmid wph wph wn ianor mpbir $.
    $( [16-Sep-1993] $)

  $( Theorem *2.26 of [WhiteheadRussell] p. 104. $)
  pm2.26 $p |-  ( -. ph \/ ( ( ph -> ps ) -> ps ) ) $=
    wph wn wph wps wi wps wi wph wps wi wph wn wn wps wph wn wn wph wps wph
    nega imim1i com12 orri $.
    $( [5-Jun-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.18 of [WhiteheadRussell] p. 124.  This theorem says that
     logical equivalence is the same as negated "exclusive-or." $)
  pm5.18 $p |- ( ( ph <-> ps ) <-> -. ( ph <-> -. ps ) ) $=
    wph wps wb wps wph wb wph wps wn wb wn wph wps bicom wph wps wn wb wps wph
    wb wph wps wn wb wps wn wph wb wps wph wb wn wph wps wn bicom wps wn wph wb
    wps wph wb wn wps wn wph wb wps wph wi wph wps wi wa wn wps wph wb wn wps
    wn wph wb wps wph wi wph wps wi wn wi wps wph wi wph wps wi wa wn wps wph
    wi wps wn wph wb wph wps wi wn wps wph wi wps wn wph wb wph wps wn wa wph
    wps wi wn wps wph wi wps wn wph wi wph wps wn wi wa wph wps wn wa wps wn
    wph wb wps wph wi wps wn wph wi wph wph wps wn wi wps wn wps wph pm2.61 wps
    wph wi wps wph wn wi wps wn wph wps wn wi wps wph pm2.65 wph wps con2 syl5
    anim12d wps wn wph bi syl5ib wph wps annim syl6ib com12 wps wph wi wph wps
    wi imnan sylib wps wph wb wps wph wi wph wps wi wa wps wph bi negbii sylibr
    wps wph wb wn wps wph wi wph wps wi wa wn wps wn wph wb wps wph wb wps wph
    wi wph wps wi wa wps wph bi negbii wps wph wi wn wph wps wi wn wo wps wn
    wph wi wph wps wn wi wa wps wph wi wph wps wi wa wn wps wn wph wb wps wph
    wi wn wps wn wph wi wph wps wn wi wa wph wps wi wn wps wph wi wn wps wn wph
    wi wph wps wn wi wps wph pm2.5 wps wph wi wn wps wph wn wa wph wps wn wi
    wps wph annim wph wn wph wps wn wi wps wph wps wn pm2.21 adantl sylbir jca
    wph wps wi wn wps wn wph wi wph wps wn wi wph wps wi wn wph wps wn wa wps
    wn wph wi wph wps annim wph wps wn wph wi wps wn wph wps wn ax-1 adantr
    sylbir wph wps pm2.51 jca jaoi wps wph wi wph wps wi ianor wps wn wph bi
    3imtr4 sylbi impbi bitr con2bii bitr $.
    $( [28-Jun-2002] $)

  $( Move negation outside of biconditional.  Compare Theorem *5.18 of
     [WhiteheadRussell] p. 124. $)
  nbbn $p |- ( ( -. ph <-> ps ) <-> -. ( ph <-> ps ) ) $=
    wph wn wps wb wps wph wn wb wph wps wb wn wph wn wps bicom wph wps wb wps
    wph wn wb wph wps wb wps wph wb wps wph wn wb wn wph wps bicom wps wph
    pm5.18 bitr con2bii bitr $.
    $( [27-Jun-2002] $)

  $( Theorem *5.11 of [WhiteheadRussell] p. 123. $)
  pm5.11 $p |-  ( ( ph -> ps ) \/ ( -. ph -> ps ) ) $=
    wph wps wi wph wn wps wi wph wps pm2.5 orri $.
    $( [17-Jun-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.12 of [WhiteheadRussell] p. 123. $)
  pm5.12 $p |-  ( ( ph -> ps ) \/ ( ph -> -. ps ) ) $=
    wph wps wi wph wps wn wi wph wps pm2.51 orri $.
    $( [17-Jun-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.13 of [WhiteheadRussell] p. 123. $)
  pm5.13 $p |-  ( ( ph -> ps ) \/ ( ps -> ph ) ) $=
    wph wps wi wps wph wi wph wps pm2.521 orri $.
    $( [7-Jun-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.14 of [WhiteheadRussell] p. 123. $)
  pm5.14 $p |-  ( ( ph -> ps ) \/ ( ps -> ch ) ) $=
    wph wps wi wps wch wi wph wps wi wn wps wch wps wph wps wi wps wph ax-1
    con3i pm2.21d orri $.
    $( [17-Jun-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.15 of [WhiteheadRussell] p. 124. $)
  pm5.15 $p |-  ( ( ph <-> ps ) \/ ( ph <-> -. ps ) ) $=
    wph wps wb wph wps wn wb wph wps wn wb wph wps wb wph wps wb wph wps wn wb
    wn wph wps pm5.18 biimpr con1i orri $.
    $( [1-Feb-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.16 of [WhiteheadRussell] p. 124. $)
  pm5.16 $p |-  -. ( ( ph <-> ps ) /\ ( ph <-> -. ps ) ) $=
    wph wps wb wph wps wn wb wa wn wph wps wb wn wph wps wn wb wn wo wph wps wb
    wph wps wn wb wn wi wph wps wb wn wph wps wn wb wn wo wph wps wb wph wps wn
    wb wn wph wps pm5.18 biimp wph wps wb wph wps wn wb pm4.62 mpbi wph wps wb
    wph wps wn wb ianor mpbir $.
    $( [17-Jun-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.17 of [WhiteheadRussell] p. 124. $)
  pm5.17 $p |-  ( ( ( ph \/ ps ) /\ -. ( ph /\ ps ) ) <-> ( ph <-> -. ps ) ) $=
    wph wps wo wph wps wa wn wa wps wn wph wi wph wps wn wi wa wps wn wph wb
    wph wps wn wb wph wps wo wps wn wph wi wph wps wa wn wph wps wn wi wph wps
    wo wps wph wo wps wn wph wi wph wps orcom wps wph df-or bitr wph wps wn wi
    wph wps wa wn wph wps imnan bicomi anbi12i wps wn wph bi wps wn wph bicom
    3bitr2 $.
    $( [22-Mar-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.19 of [WhiteheadRussell] p. 124. $)
  pm5.19 $p |-  -. ( ph <-> -. ph ) $=
    wph wph wb wph wph wn wb wn wph pm4.2 wph wph pm5.18 mpbi $.
    $( [1-Feb-2005] $) $( [3-Jan-2005] $)

  $( An alternate definition of the biconditional.  Theorem *5.23 of
     [WhiteheadRussell] p. 124. $)
  dfbi $p |- ( ( ph <-> ps ) <-> ( ( ph /\ ps ) \/ ( -. ph /\ -. ps ) ) ) $=
    wph wps wb wph wps wn wb wn wph wps wa wph wn wps wn wa wo wph wps pm5.18
    wph wps wa wph wn wps wn wa wo wph wps wn wb wph wps wn wi wps wn wph wi wa
    wph wps wa wn wph wn wps wn wa wn wa wph wps wn wb wph wps wa wph wn wps wn
    wa wo wn wph wps wn wi wph wps wa wn wps wn wph wi wph wn wps wn wa wn wph
    wps imnan wps wn wph wi wph wn wps wi wph wn wps wn wa wn wps wph bi2.15
    wph wn wps iman bitr anbi12i wph wps wn bi wph wps wa wph wn wps wn wa
    ioran 3bitr4r con1bii bitr $.
    $( [27-Jun-2002] $)

  $( Two ways to express "exclusive or."  Theorem *5.22 of [WhiteheadRussell]
     p. 124. $)
  xor $p |-  ( -. ( ph <-> ps ) <->
                ( ( ph /\ -. ps ) \/ ( ps /\ -. ph ) ) ) $=
    wph wn wps wb wph wn wps wa wph wn wn wps wn wa wo wph wps wb wn wph wps wn
    wa wps wph wn wa wo wph wn wps dfbi wph wps nbbn wph wn wps wa wph wn wn
    wps wn wa wo wps wph wn wa wph wps wn wa wo wph wps wn wa wps wph wn wa wo
    wps wph wn wa wph wn wps wa wph wps wn wa wph wn wn wps wn wa wps wph wn
    ancom wph wph wn wn wps wn wph pm4.13 anbi1i orbi12i wps wph wn wa wph wps
    wn wa orcom bitr3 3bitr3 $.
    $( [11-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.24 of [WhiteheadRussell] p. 124. $)
  pm5.24 $p |-  ( -. ( ( ph /\ ps ) \/ ( -. ph /\ -. ps ) ) <->
                ( ( ph /\ -. ps ) \/ ( ps /\ -. ph ) ) ) $=
    wph wps wa wph wn wps wn wa wo wn wph wps wb wn wph wps wn wa wps wph wn wa
    wo wph wps wb wph wps wa wph wn wps wn wa wo wph wps dfbi negbii wph wps
    xor bitr3 $.
    $( [11-Feb-2005] $) $( [3-Jan-2005] $)

  $( Two ways to express "exclusive or." $)
  xor2 $p |-  ( -. ( ph <-> ps ) <-> ( ( ph \/ ps ) /\ -. ( ph /\ ps ) ) ) $=
    wph wps wb wn wph wps wn wa wps wph wn wa wo wph wps wo wph wps wa wn wa
    wph wps xor wph wps wa wph wn wps wn wa wo wn wph wps wa wn wph wn wps wn
    wa wn wa wph wps wn wa wps wph wn wa wo wph wps wo wph wps wa wn wa wph wps
    wa wph wn wps wn wa ioran wph wps pm5.24 wph wps wa wn wph wn wps wn wa wn
    wa wph wps wa wn wph wps wo wa wph wps wo wph wps wa wn wa wph wps wo wph
    wn wps wn wa wn wph wps wa wn wph wps oran anbi2i wph wps wa wn wph wps wo
    ancom bitr3 3bitr3 bitr $.
    $( [11-Feb-2005] $) $( [3-Jan-2005] $)

  $( Two ways to express "exclusive or." $)
  xor3 $p |-  ( -. ( ph <-> ps ) <-> ( ph <-> -. ps ) ) $=
    wph wps wn wb wph wps wb wn wph wps wb wph wps wn wb wph wps pm5.18 con2bii
    bicomi $.
    $( [4-Jan-2006] $) $( [1-Jan-2006] $)

  $( Theorem *5.55 of [WhiteheadRussell] p. 125. $)
  pm5.55 $p |-  ( ( ( ph \/ ps ) <-> ph ) \/ ( ( ph \/ ps ) <-> ps ) ) $=
    wps wph wi wph wps wi wo wph wps wo wph wb wph wps wo wps wb wo wps wph
    pm5.13 wps wph wi wph wps wo wph wb wph wps wi wph wps wo wps wb wps wph wi
    wph wps wph wo wb wph wph wps wo wb wph wps wo wph wb wps wph pm4.72 wps
    wph wo wph wps wo wph wps wph orcom bibi2i wph wph wps wo bicom 3bitr wph
    wps wi wps wph wps wo wb wph wps wo wps wb wph wps pm4.72 wps wph wps wo
    bicom bitr orbi12i mpbi $.
    $( [7-Jun-2005] $) $( [3-Jan-2005] $)


$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Miscellaneous theorems of propositional calculus
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

  $( Two propositions are equivalent if they are both true.  Theorem *5.1 of
     [WhiteheadRussell] p. 123. $)
  pm5.1 $p |- ( ( ph /\ ps ) -> ( ph <-> ps ) ) $=
    wph wps wph wps wb wph wps pm5.501 biimpa $.
    $( [21-May-1994] $)

  $( Two propositions are equivalent if they are both false.  Theorem *5.21 of
     [WhiteheadRussell] p. 124. $)
  pm5.21 $p |- ( ( -. ph /\ -. ps ) -> ( ph <-> ps ) ) $=
    wph wn wps wn wa wph wps wph wn wps wn pm5.1 con4bid $.
    $( [21-May-1994] $)


  ${
    pm5.21ni.1 $e |- ( ph -> ps ) $.
    pm5.21ni.2 $e |- ( ch -> ps ) $.
    $( Two propositions implying a false one are equivalent. $)
    pm5.21ni $p |- ( -. ps -> ( ph <-> ch ) ) $=
      wph wn wch wn wph wch wb wps wn wph wch pm5.21 wph wps pm5.21ni.1 con3i
      wch wps pm5.21ni.2 con3i sylanc $.
      $( [16-Feb-1996] $)

    ${
      pm5.21nii.3 $e |- ( ps -> ( ph <-> ch ) ) $.
      $( Eliminate an antecedent implied by each side of a biconditional. $)
      pm5.21nii $p |- ( ph <-> ch ) $=
        wps wph wch wb pm5.21nii.3 wph wps wch pm5.21ni.1 pm5.21ni.2 pm5.21ni
        pm2.61i $.
        $( [21-May-1999] $)
    $}
  $}

  ${
    pm5.21nd.1 $e |- ( ( ph /\ ps ) -> th ) $.
    pm5.21nd.2 $e |- ( ( ph /\ ch ) -> th ) $.
    pm5.21nd.3 $e |- ( th -> ( ps <-> ch ) ) $.
    $( Eliminate an antecedent implied by each side of a biconditional. $)
    pm5.21nd $p |- ( ph -> ( ps <-> ch ) ) $=
      wph wth wps wch wb wph wth wn wps wn wch wn wa wps wch wb wph wth wn wps
      wn wch wn wph wps wth wph wps wth pm5.21nd.1 ex con3d wph wch wth wph wch
      wth pm5.21nd.2 ex con3d jcad wps wch pm5.21 syl6 pm5.21nd.3 pm2.61d2 $.
      $( [23-Nov-2005] $) $( [20-Nov-2005] $)
  $}

  $( Transfer negation via an equivalence. $)
  bibif $p |- ( -. ps -> ( ( ph <-> ps ) <-> -. ph ) ) $=
    wps wn wph wps wb wph wn wph wps wb wps wn wph wn wph wps wb wph wps wph
    wps bi1 con3d com12 wph wn wps wn wph wps wb wph wps pm5.21 expcom impbid
    $.
    $( [7-Nov-2007] $) $( [3-Oct-2007] $)

  $( Theorem *5.35 of [WhiteheadRussell] p. 125. $)
  pm5.35 $p |-  ( ( ( ph -> ps ) /\ ( ph -> ch ) ) ->
                ( ph -> ( ps <-> ch ) ) ) $=
    wph wps wi wph wch wi wa wph wps wch wph wps wi wph wch wi pm5.1 pm5.74rd
    $.
    $( [28-Jun-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.54 of [WhiteheadRussell] p. 125. $)
  pm5.54 $p |-  ( ( ( ph /\ ps ) <-> ph ) \/ ( ( ph /\ ps ) <-> ps ) ) $=
    wph wps wa wph wb wph wps wa wps wb wph wps wa wph wps wa wph wb wps wph
    wps wph wps wa wph wb wph wps wa wph pm5.1 anabss1 wps wph wph wps wa wps
    wph iba bicomd pm5.21ni orri $.
    $( [28-Jun-2005] $) $( [3-Jan-2005] $)

  $( Elimination of antecedents in an implication. (The proof was shortened by
     Juha Arpiainen, 19-Jan-06.) $)
  elimant $p |- ( ( ( ph -> ps ) /\ ( ( ps -> ch ) -> ( ph -> th ) ) ) ->
                ( ph -> ( ch -> th ) ) ) $=
    wph wps wi wps wch wi wph wth wi wi wa wch wph wth wph wps wi wps wch wi
    wph wth wi wi wa wps wch wi wph wth wi wch wph wps wi wps wch wi wph wth wi
    wi pm3.27 wch wps ax-1 syl5 com23 $.
    $( [21-Jan-2006] $) $( [13-Oct-1999] $)

  ${
    baib.1 $e |- ( ph <-> ( ps /\ ch ) ) $.
    $( Move conjunction outside of biconditional. $)
    baib $p |- ( ps -> ( ph <-> ch ) ) $=
      wps wch wps wch wa wph wps wch ibar baib.1 syl6rbbr $.
      $( [13-May-1999] $)
  $}

  ${
    baibr.1 $e |- ( ph <-> ( ps /\ ch ) ) $.
    $( Move conjunction outside of biconditional. $)
    baibr $p |- ( ps -> ( ch <-> ph ) ) $=
      wps wph wch wph wps wch baibr.1 baib bicomd $.
      $( [11-Jul-1994] $)
  $}

  $( Theorem *5.44 of [WhiteheadRussell] p. 125. $)
  pm5.44 $p |-  ( ( ph -> ps ) -> ( ( ph -> ch ) <->
                ( ph -> ( ps /\ ch ) ) ) ) $=
    wph wps wch wa wi wph wps wi wph wch wi wph wps wch jcab baibr $.
    $( [28-Jun-2005] $) $( [3-Jan-2005] $)

  $( Conjunction in antecedent versus disjunction in consequent.  Theorem *5.6
     of [WhiteheadRussell] p. 125. $)
  pm5.6 $p |-  ( ( ( ph /\ -. ps ) -> ch ) <-> ( ph -> ( ps \/ ch ) ) ) $=
    wph wps wn wa wch wi wph wps wn wch wi wi wph wps wch wo wi wph wps wn wch
    impexp wps wch wo wps wn wch wi wph wps wch df-or imbi2i bitr4 $.
    $( [22-Mar-2005] $) $( [8-Jun-1994] $)

  $( Theorem to move a conjunct in and out of a negation. $)
  nan $p |- ( ( ph -> -. ( ps /\ ch ) ) <-> ( ( ph /\ ps ) -> -. ch ) ) $=
    wph wps wa wch wn wi wph wps wch wn wi wi wph wps wch wa wn wi wph wps wch
    wn impexp wps wch wn wi wps wch wa wn wph wps wch imnan imbi2i bitr2 $.
    $( [9-Nov-2003] $) $( [9-Nov-2003] $)

  ${
    orcanai.1 $e |- ( ph -> ( ps \/ ch ) ) $.
    $( Change disjunction in consequent to conjunction in antecedent. $)
    orcanai $p |- ( ( ph /\ -. ps ) -> ch ) $=
      wph wps wn wch wph wps wch orcanai.1 ord imp $.
      $( [8-Jun-1994] $)
  $}


  ${
    intnan.1 $e |- -. ph $.
    $( Introduction of conjunct inside of a contradiction. $)
    intnan $p |- -. ( ps /\ ph ) $=
      wps wph wa wph intnan.1 wps wph pm3.27 mto $.
      $( [16-Sep-1993] $)

    $( Introduction of conjunct inside of a contradiction. $)
    intnanr $p |- -. ( ph /\ ps ) $=
      wph wps wa wph intnan.1 wph wps pm3.26 mto $.
      $( [3-Apr-1995] $)
  $}

  ${
    intnand.1 $e |- ( ph -> -. ps ) $.
    $( Introduction of conjunct inside of a contradiction. $)
    intnand $p |- ( ph -> -. ( ch /\ ps ) ) $=
      wph wps wch wps wa intnand.1 wch wps pm3.27 nsyl $.
      $( [12-Jul-2005] $) $( [10-Jul-2005] $)

    $( Introduction of conjunct inside of a contradiction. $)
    intnanrd $p |- ( ph -> -. ( ps /\ ch ) ) $=
      wph wps wps wch wa intnand.1 wps wch pm3.26 nsyl $.
      $( [12-Jul-2005] $) $( [10-Jul-2005] $)
  $}

  ${
    mpan.1 $e |- ph $.
    mpan.2 $e |- ( ( ph /\ ps ) -> ch ) $.
    $( An inference based on modus ponens. $)
    mpan $p |- ( ps -> ch ) $=
      wph wps wch wi mpan.1 wph wps wch mpan.2 ex ax-mp $.
      $( [30-Aug-1993] $)
  $}

  ${
    mpan2.1 $e |- ps $.
    mpan2.2 $e |- ( ( ph /\ ps ) -> ch ) $.
    $( An inference based on modus ponens. $)
    mpan2 $p |- ( ph -> ch ) $=
      wph wps wch mpan2.1 wph wps wch mpan2.2 ex mpi $.
      $( [16-Sep-1993] $)
  $}

  ${
    mp2an.1 $e |- ph $.
    mp2an.2 $e |- ps $.
    mp2an.3 $e |- ( ( ph /\ ps ) -> ch ) $.
    $( An inference based on modus ponens. $)
    mp2an $p |- ch $=
      wps wch mp2an.2 wph wps wch mp2an.1 mp2an.3 mpan ax-mp $.
      $( [13-Apr-1995] $)
  $}

  ${
    mpani.1 $e |- ps $.
    mpani.2 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    $( An inference based on modus ponens. $)
    mpani $p |- ( ph -> ( ch -> th ) ) $=
      wph wps wch wth wi mpani.1 wph wps wch wth mpani.2 exp3a mpi $.
      $( [10-Apr-1994] $)
  $}

  ${
    mpan2i.1 $e |- ch $.
    mpan2i.2 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    $( An inference based on modus ponens. $)
    mpan2i $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth mpan2i.1 wph wps wch wth mpan2i.2 exp3a mpii $.
      $( [10-Apr-1994] $)
  $}

  ${
    mp2ani.1 $e |- ps $.
    mp2ani.2 $e |- ch $.
    mp2ani.3 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    $( An inference based on modus ponens. $)
    mp2ani $p |- ( ph -> th ) $=
      wph wch wth mp2ani.2 wph wps wch wth mp2ani.1 mp2ani.3 mpani mpi $.
      $( [13-Dec-2004] $) $( [12-Dec-2004] $)
  $}

  ${
    mpand.1 $e |- ( ph -> ps ) $.
    mpand.2 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    $( A deduction based on modus ponens. $)
    mpand $p |- ( ph -> ( ch -> th ) ) $=
      wph wps wch wth wi mpand.1 wph wps wch wth mpand.2 exp3a mpd $.
      $( [13-Dec-2004] $) $( [12-Dec-2004] $)
  $}

  ${
    mpan2d.1 $e |- ( ph -> ch ) $.
    mpan2d.2 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    $( A deduction based on modus ponens. $)
    mpan2d $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth mpan2d.1 wph wps wch wth mpan2d.2 exp3a mpid $.
      $( [13-Dec-2004] $) $( [12-Dec-2004] $)
  $}

  ${
    mp2and.1 $e |- ( ph -> ps ) $.
    mp2and.2 $e |- ( ph -> ch ) $.
    mp2and.3 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    $( A deduction based on modus ponens. $)
    mp2and $p |- ( ph -> th ) $=
      wph wch wth mp2and.2 wph wps wch wth mp2and.1 mp2and.3 mpand mpd $.
      $( [13-Dec-2004] $) $( [12-Dec-2004] $)
  $}

  ${
    mpdan.1 $e |- ( ph -> ps ) $.
    mpdan.2 $e |- ( ( ph /\ ps ) -> ch ) $.
    $( An inference based on modus ponens. $)
    mpdan $p |- ( ph -> ch ) $=
      wph wps wch mpdan.1 wph wps wch mpdan.2 ex mpd $.
      $( [23-May-1999] $)
  $}

  ${
    mpancom.1 $e |- ( ps -> ph ) $.
    mpancom.2 $e |- ( ( ph /\ ps ) -> ch ) $.
    $( An inference based on modus ponens with commutation of antecedents. $)
    mpancom $p |- ( ps -> ch ) $=
      wps wph wch mpancom.1 wph wps wch mpancom.2 ancoms mpdan $.
      $( [13-Mar-2004] $) $( [28-Oct-2003] $)
  $}

  ${
    mpanl1.1 $e |- ph $.
    mpanl1.2 $e |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mpanl1 $p |- ( ( ps /\ ch ) -> th ) $=
      wps wch wth wph wps wch wth wi mpanl1.1 wph wps wa wch wth mpanl1.2 ex
      mpan imp $.
      $( [16-Aug-1994] $)
  $}

  ${
    mpanl2.1 $e |- ps $.
    mpanl2.2 $e |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mpanl2 $p |- ( ( ph /\ ch ) -> th ) $=
      wph wch wth wph wps wch wth wi mpanl2.1 wph wps wa wch wth mpanl2.2 ex
      mpan2 imp $.
      $( [16-Aug-1994] $)
  $}

  ${
    mpanl12.1 $e |- ph $.
    mpanl12.2 $e |- ps $.
    mpanl12.3 $e |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mpanl12 $p |- ( ch -> th ) $=
      wps wch wth mpanl12.2 wph wps wch wth mpanl12.1 mpanl12.3 mpanl1 mpan $.
      $( [15-Jul-2005] $) $( [13-Jul-2005] $)
  $}

  ${
    mpanr1.1 $e |- ps $.
    mpanr1.2 $e |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $.
    $( An inference based on modus ponens. $)
    mpanr1 $p |- ( ( ph /\ ch ) -> th ) $=
      wph wch wth wph wps wch wth mpanr1.1 wph wps wch wa wth mpanr1.2 ex mpani
      imp $.
      $( [3-May-1994] $)
  $}

  ${
    mpanr2.1 $e |- ch $.
    mpanr2.2 $e |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $.
    $( An inference based on modus ponens. $)
    mpanr2 $p |- ( ( ph /\ ps ) -> th ) $=
      wph wps wth wph wps wch wth mpanr2.1 wph wps wch wa wth mpanr2.2 ex
      mpan2i imp $.
      $( [3-May-1994] $)
  $}

  ${
    mpanlr1.1 $e |- ps $.
    mpanlr1.2 $e |- ( ( ( ph /\ ( ps /\ ch ) ) /\ th ) -> ta ) $.
    $( An inference based on modus ponens. $)
    mpanlr1 $p |- ( ( ( ph /\ ch ) /\ th ) -> ta ) $=
      wph wch wa wth wta wph wps wch wth wta wi mpanlr1.1 wph wps wch wa wa wth
      wta mpanlr1.2 ex mpanr1 imp $.
      $( [7-Jan-2005] $) $( [30-Dec-2004] $)
  $}

  $( Modus-tollens-like theorem. $)
  mtt $p |- ( -. ph -> ( -. ps <-> ( ps -> ph ) ) ) $=
    wph wn wps wn wps wph wi wps wph pm2.21 wps wph wi wph wn wps wn wps wph
    con3 com12 impbid2 $.
    $( [7-Apr-2001] $)

  ${
    mt2bi.1 $e |- ph $.
    $( A false consequent falsifies an antecedent. $)
    mt2bi $p |- ( -. ps <-> ( ps -> -. ph ) ) $=
      wps wn wps wph wn wi wps wph wn pm2.21 wps wph wn wi wph wps wn mt2bi.1
      wps wph con2 mpi impbi $.
      $( [19-Aug-1993] $)
  $}

  ${
    mtbid.min $e |- ( ph -> -. ps ) $.
    mtbid.maj $e |- ( ph -> ( ps <-> ch ) ) $.
    $( A deduction from a biconditional, similar to modus tollens. $)
    mtbid $p |- ( ph -> -. ch ) $=
      wph wch wps mtbid.min wph wps wch mtbid.maj biimprd mtod $.
      $( [26-Nov-1995] $)
  $}

  ${
    mtbird.min $e |- ( ph -> -. ch ) $.
    mtbird.maj $e |- ( ph -> ( ps <-> ch ) ) $.
    $( A deduction from a biconditional, similar to modus tollens. $)
    mtbird $p |- ( ph -> -. ps ) $=
      wph wps wch mtbird.min wph wps wch mtbird.maj biimpd mtod $.
      $( [10-May-1994] $)
  $}

  ${
    mtbii.min $e |- -. ps $.
    mtbii.maj $e |- ( ph -> ( ps <-> ch ) ) $.
    $( An inference from a biconditional, similar to modus tollens. $)
    mtbii $p |- ( ph -> -. ch ) $=
      wph wch wps mtbii.min wph wps wch mtbii.maj biimprd mtoi $.
      $( [27-Nov-1995] $)
  $}

  ${
    mtbiri.min $e |- -. ch $.
    mtbiri.maj $e |- ( ph -> ( ps <-> ch ) ) $.
    $( An inference from a biconditional, similar to modus tollens. $)
    mtbiri $p |- ( ph -> -. ps ) $=
      wph wps wch mtbiri.min wph wps wch mtbiri.maj biimpd mtoi $.
      $( [24-Aug-1995] $)
  $}

  ${
    2th.1 $e |- ph $.
    2th.2 $e |- ps $.
    $( Two truths are equivalent. $)
    2th $p |- ( ph <-> ps ) $=
      wph wps wps wph 2th.2 a1i wph wps 2th.1 a1i impbi $.
      $( [18-Aug-1993] $)
  $}

  ${
    2false.1 $e |- -. ph $.
    2false.2 $e |- -. ps $.
    $( Two falsehoods are equivalent. $)
    2false $p |- ( ph <-> ps ) $=
      wph wn wps wn wph wps wb 2false.1 2false.2 wph wps pm5.21 mp2an $.
      $( [5-Apr-2005] $) $( [4-Apr-2005] $)
  $}

  ${
    tbt.1 $e |- ph $.
    $( A wff is equivalent to its equivalence with truth. (The proof was
       shortened by Juha Arpiainen, 19-Jan-06.) $)
    tbt $p |- ( ps <-> ( ps <-> ph ) ) $=
      wps wph wps wb wps wph wb wph wps wph wps wb wb tbt.1 wph wps pm5.501
      ax-mp wph wps bicom bitr $.
      $( [21-Jan-2006] $) $( [18-Aug-1993] $)
  $}

  $( The negation of a wff is equivalent to the wff's equivalence to
     falsehood.  (Contributed by Juha Arpiainen, 19-Jan-06.) $)
  nbn2 $p |- ( -. ph -> ( -. ps <-> ( ph <-> ps ) ) ) $=
    wph wn wps wn wph wps wb wph wn wps wn wph wps wb wph wps pm5.21 ex wph wps
    wb wph wn wps wn wph wps wb wph wn wps wn wb wph wps pm4.11 biimp biimpcd
    impbid $.
    $( [21-Jan-2006] $) $( [19-Jan-2006] $)

  ${
    nbn.1 $e |- -. ph $.
    $( The negation of a wff is equivalent to the wff's equivalence to
       falsehood. $)
    nbn $p |- ( -. ps <-> ( ps <-> ph ) ) $=
      wps wn wph wps wb wps wph wb wph wn wps wn wph wps wb wb nbn.1 wph wps
      nbn2 ax-mp wph wps bicom bitr $.
      $( [5-Aug-1993] $)
  $}

  ${
    nbn3.1 $e |- ph $.
    $( Transfer falsehood via equivalence. $)
    nbn3 $p |- ( -. ps <-> ( ps <-> -. ph ) ) $=
      wph wn wps wph nbn3.1 negbi nbn $.
      $( [12-Sep-2006] $) $( [11-Sep-2006] $)
  $}

  ${
    biantru.1 $e |- ph $.
    $( A wff is equivalent to its conjunction with truth. $)
    biantru $p |- ( ps <-> ( ps /\ ph ) ) $=
      wph wps wps wph wa wb biantru.1 wph wps iba ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    biantrur.1 $e |- ph $.
    $( A wff is equivalent to its conjunction with truth. $)
    biantrur $p |- ( ps <-> ( ph /\ ps ) ) $=
      wph wps wph wps wa wb biantrur.1 wph wps ibar ax-mp $.
      $( [3-Aug-1994] $)
  $}

  ${
    biantrud.1 $e |- ( ph -> ps ) $.
    $( A wff is equivalent to its conjunction with truth. $)
    biantrud $p |- ( ph -> ( ch <-> ( ch /\ ps ) ) ) $=
      wph wch wch wps wa wch wph wch wps wa wph wps wch biantrud.1 anim2i
      expcom wch wps pm3.26 impbid1 $.
      $( [2-Aug-1994] $)

    $( A wff is equivalent to its conjunction with truth. $)
    biantrurd $p |- ( ph -> ( ch <-> ( ps /\ ch ) ) ) $=
      wph wch wch wps wa wps wch wa wph wps wch biantrud.1 biantrud wch wps
      ancom syl6bb $.
      $( [1-May-1995] $)
  $}

  ${
    mpbiran.1 $e |- ( ph <-> ( ps /\ ch ) ) $.
    ${
      mpbiran.2 $e |- ps $.
      $( Detach truth from conjunction in biconditional. $)
      mpbiran $p |- ( ph <-> ch ) $=
        wph wps wch wa wch mpbiran.1 wps wch mpbiran.2 biantrur bitr4 $.
        $( [27-Feb-1996] $)
    $}

    ${
      mpbiran2.2 $e |- ch $.
      $( Detach truth from conjunction in biconditional. $)
      mpbiran2 $p |- ( ph <-> ps ) $=
        wph wps wch wa wps mpbiran.1 wch wps mpbiran2.2 biantru bitr4 $.
        $( [22-Feb-1996] $)
    $}

    ${
      mpbir2an.2 $e |- ps $.
      mpbir2an.3 $e |- ch $.
      $( Detach a conjunction of truths in a biconditional. $)
      mpbir2an $p |- ph $=
        wph wch mpbir2an.3 wph wps wch mpbiran.1 mpbir2an.2 mpbiran mpbir $.
        $( [12-May-2005] $) $( [10-May-2005] $)
    $}
  $}

  $( A wff is equivalent to itself with true antecedent. $)
  biimt $p |- ( ph -> ( ps <-> ( ph -> ps ) ) ) $=
    wph wps wph wps wi wps wph ax-1 wph wps pm2.27 impbid2 $.
    $( [28-Jan-1996] $)

  $( Theorem *5.5 of [WhiteheadRussell] p. 125. $)
  pm5.5 $p |-  ( ph -> ( ( ph -> ps ) <-> ps ) ) $=
    wph wps wph wps wi wph wps biimt bicomd $.
    $( [28-Jun-2005] $) $( [3-Jan-2005] $)

  $( Theorem *5.62 of [WhiteheadRussell] p. 125.  (Contributed by Roy F.
     Longton, 21-Jun-2005.) $)
  pm5.62 $p |-  ( ( ( ph /\ ps ) \/ -. ps ) <-> ( ph \/ -. ps ) ) $=
    wph wps wa wps wn wo wph wps wn wo wps wps wn wo wph wps wps wn ordir wps
    exmid mpbiran2 $.
    $( [22-Jun-2005] $) $( [21-Jun-2005] $)

  $( A wff is disjoined with truth is true. $)
  biort $p |- ( ph -> ( ph <-> ( ph \/ ps ) ) ) $=
    wph wph wph wps wo wph wps orc wph wph wps wo ax-1 impbid2 $.
    $( [23-May-1999] $)

  $( A wff is equivalent to its disjunction with falsehood.  Theorem *4.74 of
     [WhiteheadRussell] p. 121. $)
  biorf $p |- ( -. ph -> ( ps <-> ( ph \/ ps ) ) ) $=
    wph wn wps wph wn wps wi wph wps wo wph wn wps biimt wph wps df-or syl6bbr
    $.
    $( [23-Mar-1995] $)

  ${
    biorfi.1 $e |- -. ph $.
    $( A wff is equivalent to its disjunction with falsehood. $)
    biorfi $p |- ( ps <-> ( ps \/ ph ) ) $=
      wps wph wps wo wps wph wo wph wn wps wph wps wo wb biorfi.1 wph wps biorf
      ax-mp wph wps orcom bitr $.
      $( [23-Mar-1995] $)
  $}

  ${
    bianfi.1 $e |- -. ph $.
    $( A wff conjoined with falsehood is false. $)
    bianfi $p |- ( ph <-> ( ps /\ ph ) ) $=
      wph wps wph wa wph wps wph wa bianfi.1 pm2.21i wps wph pm3.27 impbi $.
      $( [5-Aug-1993] $)
  $}

  ${
    bianfd.1 $e |- ( ph -> -. ps ) $.
    $( A wff conjoined with falsehood is false. $)
    bianfd $p |- ( ph -> ( ps <-> ( ps /\ ch ) ) ) $=
      wph wps wps wch wa wph wps wps wch wa bianfd.1 pm2.21d wps wch pm3.26
      impbid1 $.
      $( [27-Mar-1995] $)
  $}

  $( Theorem *4.82 of [WhiteheadRussell] p. 122. $)
  pm4.82 $p |-  ( ( ( ph -> ps ) /\ ( ph -> -. ps ) ) <-> -. ph ) $=
    wph wps wi wph wps wn wi wa wph wn wph wps wi wph wps wn wi wph wn wph wps
    pm2.65 imp wph wn wph wps wi wph wps wn wi wph wps pm2.21 wph wps wn pm2.21
    jca impbi $.
    $( [28-Jun-2005] $) $( [3-Jan-2005] $)

  $( Theorem *4.83 of [WhiteheadRussell] p. 122. $)
  pm4.83 $p |-  ( ( ( ph -> ps ) /\ ( -. ph -> ps ) ) <-> ps ) $=
    wps wph wph wn wo wps wi wph wps wi wph wn wps wi wa wph wph wn wo wps wph
    exmid a1bi wph wps wph wn jaob bitr2 $.
    $( [28-Jun-2005] $) $( [3-Jan-2005] $)

  $( Negation inferred from embedded conjunct. $)
  pclem6 $p |- ( ( ph <-> ( ps /\ -. ph ) ) -> -. ps ) $=
    wph wps wph wn wa wb wph wn wps wn wph wps wph wn wa wb wph wph wps wph wn
    wa wb wph wps wph wn wa wph wn wph wps wph wn wa bi1 wps wph wn pm3.27 syl6
    pm2.01d wph wn wph wps wph wn wa wb wps wph wi wps wn wph wps wph wn wa wb
    wps wph wn wph wph wps wph wn wa wb wps wph wn wph wph wps wph wn wa bi2
    exp3a com23 wps wph con3 syli mpd $.
    $( [20-Aug-1993] $)

  $( A transitive law of equivalence.  Compare Theorem *4.22 of
     [WhiteheadRussell] p. 117. $)
  biantr $p |- ( ( ( ph <-> ps ) /\ ( ch <-> ps ) ) -> ( ph <-> ch ) ) $=
    wch wps wb wph wch wb wph wps wb wch wps wb wch wps wph wch wps wb id
    bibi2d biimparc $.
    $( [18-Aug-1993] $)


  $( Disjunction distributes over the biconditional.  An axiom of system DS in
     Vladimir Lifschitz, "On calculational proofs" (1998),
     ~ http://citeseer.ist.psu.edu/lifschitz98calculational.html . $)
  orbidi $p |-  ( ( ph \/ ( ps <-> ch ) ) <->
                ( ( ph \/ ps ) <-> ( ph \/ ch ) ) ) $=
    wph wps wch wb wo wph wps wo wph wch wo wb wph wph wps wo wph wch wo wb wps
    wch wb wph wph wps wo wph wch wo wph wph wch wo wph wps wo wph wch orc a1d
    wph wph wps wo wph wch wo wph wps orc a1d impbid wps wch wb wps wch wph wps
    wch wb id orbi2d jaoi wph wps wo wph wch wo wi wph wch wo wph wps wo wi wa
    wph wps wch wi wo wph wch wps wi wo wa wph wps wo wph wch wo wb wph wps wch
    wb wo wph wps wo wph wch wo wi wph wps wch wi wo wph wch wo wph wps wo wi
    wph wch wps wi wo wph wps wch pm2.85 wph wch wps pm2.85 anim12i wph wps wo
    wph wch wo bi wph wps wch wb wo wph wps wch wi wch wps wi wa wo wph wps wch
    wi wo wph wch wps wi wo wa wps wch wb wps wch wi wch wps wi wa wph wps wch
    bi orbi2i wph wps wch wi wch wps wi ordi bitr 3imtr4 impbi $.
    $( [9-Jan-2005] $) $( [8-Jan-2005] $)

  $( Associative law for the biconditional.  An axiom of system DS in Vladimir
     Lifschitz, "On calculational proofs" (1998),
     ~ http://citeseer.ist.psu.edu/lifschitz98calculational.html .
     Interestingly, this law was not included in _Principia Mathematica_ but
     was apparently first noted by Jan Lukasiewicz circa 1923.  (The proof was
     shortened by Juha Arpiainen, 19-Jan-06.) $)
  biass $p |- ( ( ( ph <-> ps ) <-> ch ) <-> ( ph <-> ( ps <-> ch ) ) ) $=
    wph wph wps wb wch wb wph wps wch wb wb wb wph wps wch wb wph wps wb wch wb
    wph wps wch wb wb wph wps wph wps wb wch wph wps pm5.501 bibi1d wph wps wch
    wb pm5.501 bitr3d wph wn wps wn wch wb wps wch wb wn wph wps wb wch wb wph
    wps wch wb wb wps wn wch wb wps wch wb wn wb wph wn wps wch nbbn a1i wph wn
    wps wn wph wps wb wch wph wps nbn2 bibi1d wph wps wch wb nbn2 3bitr3d
    pm2.61i $.
    $( [21-Jan-2006] $) $( [8-Jan-2005] $)

  $( Lukasiewicz's shortest axiom for equivalential calculus.  Storrs McCall,
     ed., _Polish Logic 1920-1939_ (Oxford, 1967), p. 96. $)
  biluk $p |- ( ( ph <-> ps ) <-> ( ( ch <-> ps ) <-> ( ph <-> ch ) ) ) $=
    wph wps wb wch wps wph wch wb wb wb wch wps wb wph wch wb wb wph wps wb wch
    wb wps wph wch wb wb wb wph wps wb wch wps wph wch wb wb wb wb wph wps wb
    wch wb wps wph wb wch wb wps wph wch wb wb wph wps wb wps wph wb wch wph
    wps bicom bibi1i wps wph wch biass bitr wph wps wb wch wps wph wch wb wb
    biass mpbi wch wps wph wch wb biass bitr4 $.
    $( [11-Jan-2005] $) $( [10-Jan-2005] $)

  $( Disjunction distributes over the biconditional.  Theorem *5.7 of
     [WhiteheadRussell] p. 125.  This theorem is similar to ~ orbidi .
     (Contributed by Roy F. Longton, 21-Jun-2005.) $)
  pm5.7 $p |-  ( ( ( ph \/ ch ) <-> ( ps \/ ch ) ) <->
               ( ch \/ ( ph <-> ps ) ) ) $=
    wch wph wps wb wo wch wph wo wch wps wo wb wph wch wo wps wch wo wb wch wph
    wps orbidi wch wph wo wph wch wo wch wps wo wps wch wo wch wph orcom wch
    wps orcom bibi12i bitr2 $.
    $( [22-Jun-2005] $) $( [21-Jun-2005] $)

  $( Dijkstra-Scholten's Golden Rule for calculational proofs. $)
  bigolden $p |- ( ( ( ph /\ ps ) <-> ph ) <-> ( ps <-> ( ph \/ ps ) ) ) $=
    wph wps wi wph wph wps wa wb wps wph wps wo wb wph wps wa wph wb wph wps
    pm4.71 wph wps pm4.72 wph wph wps wa bicom 3bitr3r $.
    $( [12-Jan-2005] $) $( [10-Jan-2005] $)

  $( Theorem *5.71 of [WhiteheadRussell] p. 125.  (Contributed by Roy F.
     Longton, 23-Jun-2005.) $)
  pm5.71 $p |-  ( ( ps -> -. ch ) -> ( ( ( ph \/ ps ) /\ ch ) <->
                ( ph /\ ch ) ) ) $=
    wps wch wn wph wps wo wch wa wph wch wa wb wps wn wph wps wo wph wch wps wn
    wph wps wo wph wps wph orel2 wph wps orc impbid1 anbi1d wch wn wch wph wps
    wo wph wch wph wps wo wph wb pm2.21 pm5.32rd ja $.
    $( [24-Jun-2005] $) $( [23-Jun-2005] $)

  $( Theorem *5.75 of [WhiteheadRussell] p. 126. $)
  pm5.75 $p |-  ( ( ( ch -> -. ps ) /\ ( ph <-> ( ps \/ ch ) ) ) ->
                ( ( ph /\ -. ps ) <-> ch ) ) $=
    wch wps wn wi wph wps wch wo wb wa wph wps wn wa wch wph wps wch wo wb wph
    wps wn wa wch wi wch wps wn wi wph wps wch wo wb wph wps wch wo wi wph wps
    wn wa wch wi wph wps wch wo bi1 wph wps wch pm5.6 sylibr adantl wch wps wn
    wi wph wps wch wo wb wa wch wph wps wn wph wps wch wo wb wch wps wn wi wch
    wph wi wph wps wch wo wb wch wps wn wph wph wps wch wo wb wch wps wn wph
    wph wps wch wo wb wch wps wph wo wi wch wps wn wa wph wi wph wps wch wo wb
    wps wch wo wph wi wch wps wph wo wi wph wps wch wo bi2 wch wps wch wo wph
    wps wph wo wch wps olc wph wps olc imim12i syl wch wps wph pm5.6 sylibr
    exp3a a2d impcom wch wps wn wi wph wps wch wo wb pm3.26 jcad impbid $.
    $( [22-Mar-2005] $) $( [3-Jan-2005] $)

  $( Removal of conjunct from one side of an equivalence. $)
  bimsc1 $p |- ( ( ( ph -> ps ) /\ ( ch <-> ( ps /\ ph ) ) )
               -> ( ch <-> ph ) ) $=
    wch wps wph wa wb wch wps wph wa wph wps wi wph wch wps wph wa wb id wph
    wps wi wph wps wph wa wph wps wi wph wps wph wa wb wph wps pm4.71r biimp
    bicomd sylan9bbr $.
    $( [5-Aug-1993] $)

  ${
    ecase2d.1 $e |- ( ph -> ps ) $.
    ecase2d.2 $e |- ( ph -> -. ( ps /\ ch ) ) $.
    ecase2d.3 $e |- ( ph -> -. ( ps /\ th ) ) $.
    ecase2d.4 $e |- ( ph -> ( ta \/ ( ch \/ th ) ) ) $.
    $( Deduction for elimination by cases. $)
    ecase2d $p |- ( ph -> ta ) $=
      wph wch wth wo wn wta wph wch wn wth wn wa wch wth wo wn wph wch wn wth
      wn wph wps wch wn ecase2d.1 wph wps wch wa wn wps wch wn wi ecase2d.2 wps
      wch imnan sylibr mpd wph wps wth wn ecase2d.1 wph wps wth wa wn wps wth
      wn wi ecase2d.3 wps wth imnan sylibr mpd jca wch wth ioran sylibr wph wch
      wth wo wta wph wta wch wth wo wo wch wth wo wta wo ecase2d.4 wta wch wth
      wo orcom sylib ord mpd $.
      $( [21-Apr-1994] $)
  $}

  ${
    ecase3.1 $e |- ( ph -> ch ) $.
    ecase3.2 $e |- ( ps -> ch ) $.
    ecase3.3 $e |- ( -. ( ph \/ ps ) -> ch ) $.
    $( Inference for elimination by cases. $)
    ecase3 $p |- ch $=
      wph wps wch wph wn wps wn wch wph wn wps wn wa wph wps wo wn wch wph wps
      ioran ecase3.3 sylbir ex ecase3.1 ecase3.2 pm2.61ii $.
      $( [23-Mar-1995] $)
  $}

  ${
    ecase.1 $e |- ( -. ph -> ch ) $.
    ecase.2 $e |- ( -. ps -> ch ) $.
    ecase.3 $e |- ( ( ph /\ ps ) -> ch ) $.
    $( Inference for elimination by cases. $)
    ecase $p |- ch $=
      wph wps wch wph wps wch ecase.3 ex ecase.1 ecase.2 pm2.61nii $.
      $( [22-Jul-2005] $) $( [13-Jul-2005] $)
  $}

  ${
    ecase3d.1 $e |- ( ph -> ( ps -> th ) ) $.
    ecase3d.2 $e |- ( ph -> ( ch -> th ) ) $.
    ecase3d.3 $e |- ( ph -> ( -. ( ps \/ ch ) -> th ) ) $.
    $( Deduction for elimination by cases. $)
    ecase3d $p |- ( ph -> th ) $=
      wps wch wph wth wi wph wps wth ecase3d.1 com12 wph wch wth ecase3d.2
      com12 wph wps wch wo wn wth ecase3d.3 com12 ecase3 $.
      $( [2-May-1996] $)
  $}

  ${
    ccase.1 $e |- ( ( ph /\ ps ) -> ta ) $.
    ccase.2 $e |- ( ( ch /\ ps ) -> ta ) $.
    ccase.3 $e |- ( ( ph /\ th ) -> ta ) $.
    ccase.4 $e |- ( ( ch /\ th ) -> ta ) $.
    $( Inference for combining cases. $)
    ccase $p |- ( ( ( ph \/ ch ) /\ ( ps \/ th ) ) -> ta ) $=
      wph wch wo wps wth wo wa wph wps wa wch wps wa wo wph wth wa wch wth wa
      wo wo wta wph wch wo wps wth wo wa wph wps wa wph wth wa wo wch wps wa
      wch wth wa wo wo wph wps wa wch wps wa wo wph wth wa wch wth wa wo wo wph
      wch wps wth anddi wph wps wa wph wth wa wch wps wa wch wth wa or4 bitr
      wph wps wa wch wps wa wo wta wph wth wa wch wth wa wo wph wps wa wta wch
      wps wa ccase.1 ccase.2 jaoi wph wth wa wta wch wth wa ccase.3 ccase.4
      jaoi jaoi sylbi $.
      $( [29-Jul-1999] $)
  $}

  ${
    $v et $. $( Greek eta $)
    ccasedwet $f wff et $.
    ccased.1 $e |- ( ph -> ( ( ps /\ ch ) -> et ) ) $.
    ccased.2 $e |- ( ph -> ( ( th /\ ch ) -> et ) ) $.
    ccased.3 $e |- ( ph -> ( ( ps /\ ta ) -> et ) ) $.
    ccased.4 $e |- ( ph -> ( ( th /\ ta ) -> et ) ) $.
    $( Deduction for combining cases. $)
    ccased $p |- ( ph -> ( ( ( ps \/ th ) /\ ( ch \/ ta ) ) -> et ) ) $=
      wph wps wch wa wth wch wa wo wps wta wa wth wta wa wo wo ccasedwet wps
      wth wo wch wta wo wa wph wps wch wa wth wch wa wo ccasedwet wps wta wa
      wth wta wa wo wph wps wch wa ccasedwet wth wch wa ccased.1 ccased.2 jaod
      wph wps wta wa ccasedwet wth wta wa ccased.3 ccased.4 jaod jaod wps wth
      wo wch wta wo wa wps wch wa wps wta wa wo wth wch wa wth wta wa wo wo wps
      wch wa wth wch wa wo wps wta wa wth wta wa wo wo wps wth wch wta anddi
      wps wch wa wps wta wa wth wch wa wth wta wa or4 bitr syl5ib $.
      $( [10-May-2004] $) $( [9-May-2004] $)
  $}

  ${
    ccase2.1 $e |- ( ( ph /\ ps ) -> ta ) $.
    ccase2.2 $e |- ( ch -> ta ) $.
    ccase2.3 $e |- ( th -> ta ) $.
    $( Inference for combining cases. $)
    ccase2 $p |- ( ( ( ph \/ ch ) /\ ( ps \/ th ) ) -> ta ) $=
      wph wps wch wth wta ccase2.1 wch wta wps ccase2.2 adantr wth wta wph
      ccase2.3 adantl wth wta wch ccase2.3 adantl ccase $.
      $( [29-Jul-1999] $)
  $}

  ${
    4cases.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    4cases.2 $e |- ( ( ph /\ -. ps ) -> ch ) $.
    4cases.3 $e |- ( ( -. ph /\ ps ) -> ch ) $.
    4cases.4 $e |- ( ( -. ph /\ -. ps ) -> ch ) $.
    $( Inference eliminating two antecedents from the four possible cases that
       result from their true/false combinations. $)
    4cases $p |- ch $=
      wps wch wph wps wch 4cases.1 4cases.3 pm2.61ian wph wps wn wch 4cases.2
      4cases.4 pm2.61ian pm2.61i $.
      $( [25-Oct-2003] $) $( [25-Oct-2003] $)
  $}

  ${
    niabn.1 $e |- ph $.
    $( Miscellaneous inference relating falsehoods. $)
    niabn $p |- ( -. ps -> ( ( ch /\ ps ) <-> -. ph ) ) $=
      wch wps wa wps wph wn wch wps pm3.27 wph wps niabn.1 pm2.24i pm5.21ni $.
      $( [31-Mar-1994] $)
  $}

  $( Lemma for an alternate version of weak deduction theorem. $)
  dedlem0a $p |- ( ph -> ( ps <-> ( ( ch -> ph ) -> ( ps /\ ph ) ) ) ) $=
    wph wps wch wph wi wps wi wch wph wi wps wph wa wi wph wps wch wph wi wps
    wi wps wch wph wi ax-1 wch wph wi wps wi wph wps wph wch wph wi wps wph wch
    ax-1 imim1i com12 impbid2 wph wps wps wph wa wch wph wi wph wps iba imbi2d
    bitrd $.
    $( [2-Apr-1994] $)

  $( Lemma for an alternate version of weak deduction theorem. $)
  dedlem0b $p |- ( -. ph -> ( ps <-> ( ( ps -> ph ) -> ( ch /\ ph ) ) ) ) $=
    wph wn wps wps wph wi wch wph wa wi wph wn wps wph wi wps wch wph wa wph wn
    wph wch wph wa wps wph wch wph wa pm2.21 imim2d com23 wps wph wi wch wph wa
    wi wph wn wps wps wph wi wch wph wa wi wps wph wps wn wps wph wi wch wph wa
    wph wps wph pm2.21 wch wph pm3.27 imim12i con1d com12 impbid $.
    $( [2-Apr-1994] $)

  $( Lemma for weak deduction theorem. $)
  dedlema $p |- ( ph -> ( ps <-> ( ( ps /\ ph ) \/ ( ch /\ -. ph ) ) ) ) $=
    wph wps wps wch wph wn wa wo wps wph wa wch wph wn wa wo wph wps wps wch
    wph wn wa wo wps wch wph wn wa orc wph wps wps wch wph wn wa wph wps idd
    wph wph wn wps wch wph wps pm2.24 adantld jaod impbid2 wph wps wps wph wa
    wch wph wn wa wph wps iba orbi1d bitrd $.
    $( [26-Jun-2002] $)

  $( Lemma for weak deduction theorem. $)
  dedlemb $p |- ( -. ph -> ( ch <-> ( ( ps /\ ph ) \/ ( ch /\ -. ph ) ) ) ) $=
    wph wn wch wps wph wa wch wph wn wa wo wch wph wn wps wph wa wch wph wn wa
    wo wch wph wn wa wps wph wa olc expcom wph wn wps wph wa wch wch wph wn wa
    wph wn wps wph wch wph wn wph wps wch wph wps wch wi pm2.21 com23 imp3a wch
    wph wn wa wch wi wph wn wch wph wn pm3.26 a1i jaod impbid $.
    $( [15-May-1999] $)

  ${
    elimh.1 $e |- ( ( ph <-> ( ( ph /\ ch ) \/ ( ps /\ -. ch ) ) )
                     -> ( ch <-> ta ) ) $.
    elimh.2 $e |- ( ( ps <-> ( ( ph /\ ch ) \/ ( ps /\ -. ch ) ) )
                     -> ( th <-> ta ) ) $.
    elimh.3 $e |- th $.
    $( Hypothesis builder for weak deduction theorem.  For more information,
       see the Deduction Theorem link on the Metamath Proof Explorer home
       page. $)
    elimh $p |- ta $=
      wch wta wch wta wch wph wph wch wa wps wch wn wa wo wb wch wta wb wch wph
      wps dedlema elimh.1 syl ibi wch wn wth wta elimh.3 wch wn wps wph wch wa
      wps wch wn wa wo wb wth wta wb wch wph wps dedlemb elimh.2 syl mpbii
      pm2.61i $.
      $( [26-Jun-2002] $)
  $}

  ${
    dedt.1 $e |- ( ( ph <-> ( ( ph /\ ch ) \/ ( ps /\ -. ch ) ) )
                     -> ( th <-> ta ) ) $.
    dedt.2 $e |- ta $.
    $( The weak deduction theorem.  For more information, see the Deduction
       Theorem link on the Metamath Proof Explorer home page. $)
    dedt $p |- ( ch -> th ) $=
      wch wph wph wch wa wps wch wn wa wo wb wth wch wph wps dedlema wph wph
      wch wa wps wch wn wa wo wb wth wta dedt.2 dedt.1 mpbiri syl $.
      $( [26-Jun-2002] $)
  $}

  $( Contraposition.  Theorem *2.16 of [WhiteheadRussell] p. 103.  This version
     of ~ con3 demonstrates the use of the weak deduction theorem to derive
     it from ~ con3i . $)
  con3th $p |- ( ( ph -> ps ) -> ( -. ps -> -. ph ) ) $=
    wps wph wph wps wi wps wn wph wn wi wps wph wps wi wa wph wph wps wi wn wa
    wo wn wph wn wi wps wps wph wps wi wa wph wph wps wi wn wa wo wb wps wn wps
    wph wps wi wa wph wph wps wi wn wa wo wn wph wn wps wps wph wps wi wa wph
    wph wps wi wn wa wo wb wps wps wph wps wi wa wph wph wps wi wn wa wo wps
    wps wph wps wi wa wph wph wps wi wn wa wo wb id negbid imbi1d wph wps wph
    wps wi wa wph wph wps wi wn wa wo wps wph wph wps wi wph wph wi wph wps wph
    wps wi wa wph wph wps wi wn wa wo wi wps wps wph wps wi wa wph wph wps wi
    wn wa wo wb wps wps wph wps wi wa wph wph wps wi wn wa wo wph wps wps wph
    wps wi wa wph wph wps wi wn wa wo wb id imbi2d wph wps wph wps wi wa wph
    wph wps wi wn wa wo wb wph wps wph wps wi wa wph wph wps wi wn wa wo wph
    wph wps wph wps wi wa wph wph wps wi wn wa wo wb id imbi2d wph id elimh
    con3i dedt $.
    $( [27-Jun-2002] $)

  $( The consensus theorem.  This theorem and its dual (with ` \/ ` and ` /\ `
     interchanged) are commonly used in computer logic design to eliminate
     redundant terms from Boolean expressions.  Specifically, we prove that the
     term ` ( ps /\ ch ) ` on the left-hand side is redundant. $)
  consensus $p |- ( ( ( ( ph /\ ps ) \/ ( -. ph /\ ch ) ) \/ ( ps /\ ch ) ) <->
                      ( ( ph /\ ps ) \/ ( -. ph /\ ch ) ) ) $=
    wph wps wa wph wn wch wa wo wps wch wa wo wph wps wa wph wn wch wa wo wph
    wps wa wph wn wch wa wo wph wps wa wph wn wch wa wo wps wch wa wph wps wa
    wph wn wch wa wo id wps wch wa wps wph wa wch wph wn wa wo wph wps wa wph
    wn wch wa wo wph wps wch wa wps wph wa wch wph wn wa wo wi wph wps wps wph
    wa wch wph wn wa wo wch wph wps wps wph wa wch wph wn wa wo wph wps wch
    dedlema biimpd adantrd wph wn wch wps wph wa wch wph wn wa wo wps wph wn
    wch wps wph wa wch wph wn wa wo wph wps wch dedlemb biimpd adantld pm2.61i
    wps wph wa wph wps wa wch wph wn wa wph wn wch wa wps wph ancom wch wph wn
    ancom orbi12i sylib jaoi wph wps wa wph wn wch wa wo wps wch wa orc impbi
    $.
    $( [16-May-2003] $)

  $( Theorem *4.42 of [WhiteheadRussell] p. 119.  (Contributed by Roy F.
     Longton, 21-Jun-2005.) $)
  pm4.42 $p |-  ( ph <-> ( ( ph /\ ps ) \/ ( ph /\ -. ps ) ) ) $=
    wps wph wph wps wa wph wps wn wa wo wb wps wph wph dedlema wps wph wph
    dedlemb pm2.61i $.
    $( [21-Jun-2005] $) $( [21-Jun-2005] $)

  ${
    ninba.1 $e |- ph $.
    $( Miscellaneous inference relating falsehoods. $)
    ninba $p |- ( -. ps -> ( -. ph <-> ( ch /\ ps ) ) ) $=
      wps wn wch wps wa wph wn wph wps wch ninba.1 niabn bicomd $.
      $( [31-Mar-1994] $)
  $}

  ${
    $v et $. $( Greek eta $)
    wet $f wff et $.
    prlem1.1 $e |- ( ph -> ( et <-> ch ) ) $.
    prlem1.2 $e |- ( ps -> -. th ) $.
    $( A specialized lemma for set theory (to derive the Axiom of Pairing). $)
    prlem1 $p |- ( ph -> ( ps ->
                  ( ( ( ps /\ ch ) \/ ( th /\ ta ) ) -> et ) ) ) $=
      wps wch wa wth wta wa wo wph wps wet wps wch wa wph wps wet wi wi wth wta
      wa wps wch wa wph wet wps wch wph wet wi wps wph wet wch prlem1.1
      biimprcd adantl a1dd wth wta wa wps wet wi wph wth wps wet wi wta wth wth
      wn wet wps wth wet pm2.24 prlem1.2 syl5 adantr a1d jaoi com3l $.
      $( [18-Oct-1995] $)
  $}

  $( A specialized lemma for set theory (to derive the Axiom of Pairing). $)
  prlem2 $p |- ( ( ( ph /\ ps ) \/ ( ch /\ th ) ) <->
               ( ( ph \/ ch ) /\ ( ( ph /\ ps ) \/ ( ch /\ th ) ) ) ) $=
    wph wps wa wch wth wa wo wph wch wo wph wps wa wa wph wch wo wch wth wa wa
    wo wph wch wo wph wps wa wch wth wa wo wa wph wps wa wph wch wo wph wps wa
    wa wch wth wa wph wch wo wch wth wa wa wph wps wa wph wch wo wph wa wps wa
    wph wch wo wph wps wa wa wph wph wch wo wph wa wps wph wch orabs anbi1i wph
    wch wo wph wps anass bitr wch wth wa wph wch wo wch wa wth wa wph wch wo
    wch wth wa wa wch wph wch wo wch wa wth wch wch wph wo wch wa wph wch wo
    wch wa wch wph orabs wch wph wo wph wch wo wch wch wph orcom anbi1i bitr
    anbi1i wph wch wo wch wth anass bitr orbi12i wph wch wo wph wps wa wch wth
    wa andi bitr4 $.
    $( [5-Aug-1993] $)

  ${
    oplem1.1 $e |- ( ph -> ( ps \/ ch ) ) $.
    oplem1.2 $e |- ( ph -> ( th \/ ta ) ) $.
    oplem1.3 $e |- ( ps <-> th ) $.
    oplem1.4 $e |- ( ch -> ( th <-> ta ) ) $.
    $( A specialized lemma for set theory (ordered pair theorem). $)
    oplem1 $p |- ( ph -> ps ) $=
      wph wps wn wps wi wps wph wps wn wch wta wa wps wph wps wn wch wta wph
      wps wch oplem1.1 ord wph wth wn wta wps wn wph wth wta oplem1.2 ord wps
      wth oplem1.3 negbii syl5ib jcad wch wps wta wch wth wta wps oplem1.4
      oplem1.3 syl5bb biimpar syl6 wps pm2.18 syl $.
      $( [18-Oct-1995] $)
  $}

  $( Lemma used in construction of real numbers. $)
  rnlem $p |- ( ( ( ph /\ ps ) /\ ( ch /\ th ) ) <->
  ( ( ( ph /\ ch ) /\ ( ps /\ th ) ) /\ ( ( ph /\ th ) /\ ( ps /\ ch ) ) ) ) $=
    wph wps wa wch wth wa wa wph wch wth wa wa wps wch wth wa wa wa wph wch wa
    wph wth wa wa wps wch wa wps wth wa wa wa wph wch wa wps wth wa wa wph wth
    wa wps wch wa wa wa wph wps wch wth wa anandir wph wch wth wa wa wph wch wa
    wph wth wa wa wps wch wth wa wa wps wch wa wps wth wa wa wph wch wth anandi
    wps wch wth anandi anbi12i wph wch wa wph wth wa wa wps wch wa wps wth wa
    wa wa wph wch wa wph wth wa wa wps wth wa wps wch wa wa wa wph wch wa wps
    wth wa wa wph wth wa wps wch wa wa wa wps wch wa wps wth wa wa wps wth wa
    wps wch wa wa wph wch wa wph wth wa wa wps wch wa wps wth wa ancom anbi2i
    wph wch wa wph wth wa wps wth wa wps wch wa an4 bitr 3bitr $.
    $( [4-Sep-1995] $)

  $( A single axiom for Boolean algebra known as DN_1.  See
     ~ http://www-unix.mcs.anl.gov/~~mccune/papers/basax/v12.pdf . $)
$(
  dn1 $p |- ( -. ( -. ( -. ( ph \/ ps ) \/ ch ) \/
            -. ( ph \/ -. ( -. ch \/ -. ( ch \/ th ) ) ) ) <-> ch ) $=
            ? $.
$)
    $( [@] $) $( [22-Jun-2005] $)

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Abbreviated conjunction and disjunction of three wff's
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

  $( Extend wff definition to include 3-way disjunction ('or'). $)
  w3o $a wff ( ph \/ ps \/ ch ) $.
  $( Extend wff definition to include 3-way conjunction ('and'). $)
  w3a $a wff ( ph /\ ps /\ ch ) $.

  $( These abbreviations help eliminate parentheses to aid readability. $)

  $( Define disjunction ('or') of 3 wff's.  Definition *2.33 of
     [WhiteheadRussell] p. 105.  This abbreviation reduces the number of
     parentheses and emphasizes that the order of bracketing is not
     important by virtue of the associative law ~ orass . $)
  df-3or $a |- ( ( ph \/ ps \/ ch ) <-> ( ( ph \/ ps ) \/ ch ) ) $.

  $( Define conjunction ('and') of 3 wff.s.  Definition *4.34 of
     [WhiteheadRussell] p. 118.  This abbreviation reduces the number of
     parentheses and emphasizes that the order of bracketing is not
     important by virtue of the associative law ~ anass . $)
  df-3an $a |- ( ( ph /\ ps /\ ch ) <-> ( ( ph /\ ps ) /\ ch ) ) $.

  $( Associative law for triple disjunction. $)
  3orass $p |- ( ( ph \/ ps \/ ch ) <-> ( ph \/ ( ps \/ ch ) ) ) $=
    wph wps wch w3o wph wps wo wch wo wph wps wch wo wo wph wps wch df-3or wph
    wps wch orass bitr $.
    $( [8-Apr-1994] $)

  $( Associative law for triple conjunction. $)
  3anass $p |- ( ( ph /\ ps /\ ch ) <-> ( ph /\ ( ps /\ ch ) ) ) $=
    wph wps wch w3a wph wps wa wch wa wph wps wch wa wa wph wps wch df-3an wph
    wps wch anass bitr $.
    $( [8-Apr-1994] $)

  $( Rotation law for triple conjunction. $)
  3anrot $p |- ( ( ph /\ ps /\ ch ) <-> ( ps /\ ch /\ ph ) ) $=
    wph wps wch wa wa wps wch wa wph wa wph wps wch w3a wps wch wph w3a wph wps
    wch wa ancom wph wps wch 3anass wps wch wph df-3an 3bitr4 $.
    $( [8-Apr-1994] $)

  $( Rotation law for triple disjunction. $)
  3orrot $p |- ( ( ph \/ ps \/ ch ) <-> ( ps \/ ch \/ ph ) ) $=
    wph wps wch wo wo wps wch wo wph wo wph wps wch w3o wps wch wph w3o wph wps
    wch wo orcom wph wps wch 3orass wps wch wph df-3or 3bitr4 $.
    $( [4-Apr-1995] $)

  $( Commutation law for triple conjunction. $)
  3ancoma $p |- ( ( ph /\ ps /\ ch ) <-> ( ps /\ ph /\ ch ) ) $=
    wph wps wa wch wa wps wph wa wch wa wph wps wch w3a wps wph wch w3a wph wps
    wa wps wph wa wch wph wps ancom anbi1i wph wps wch df-3an wps wph wch
    df-3an 3bitr4 $.
    $( [21-Apr-1994] $)

  $( Commutation law for triple conjunction. $)
  3ancomb $p |- ( ( ph /\ ps /\ ch ) <-> ( ph /\ ch /\ ps ) ) $=
    wph wps wch w3a wps wph wch w3a wph wch wps w3a wph wps wch 3ancoma wps wph
    wch 3anrot bitr $.
    $( [21-Apr-1994] $)

  $( Reversal law for triple conjunction. $)
  3anrev $p |- ( ( ph /\ ps /\ ch ) <-> ( ch /\ ps /\ ph ) ) $=
    wph wps wch w3a wps wph wch w3a wch wps wph w3a wph wps wch 3ancoma wch wps
    wph 3anrot bitr4 $.
    $( [21-Apr-1994] $)

  $( Simplification of triple conjunction. $)
  3simpa $p |- ( ( ph /\ ps /\ ch ) -> ( ph /\ ps ) ) $=
    wph wps wch w3a wph wps wa wch wph wps wch df-3an pm3.26bi $.
    $( [21-Apr-1994] $)

  $( Simplification of triple conjunction. $)
  3simpb $p |- ( ( ph /\ ps /\ ch ) -> ( ph /\ ch ) ) $=
    wph wps wch w3a wph wch wps w3a wph wch wa wph wps wch 3ancomb wph wch wps
    3simpa sylbi $.
    $( [21-Apr-1994] $)

  $( Simplification of triple conjunction. $)
  3simpc $p |- ( ( ph /\ ps /\ ch ) -> ( ps /\ ch ) ) $=
    wph wps wch w3a wps wch wph w3a wps wch wa wph wps wch 3anrot wps wch wph
    3simpa sylbi $.
    $( [21-Apr-1994] $)

  $( Simplification of triple conjunction. $)
  3simp1 $p |- ( ( ph /\ ps /\ ch ) -> ph ) $=
    wph wps wch w3a wph wps wph wps wch 3simpa pm3.26d $.
    $( [21-Apr-1994] $)

  $( Simplification of triple conjunction. $)
  3simp2 $p |- ( ( ph /\ ps /\ ch ) -> ps ) $=
    wph wps wch w3a wph wps wph wps wch 3simpa pm3.27d $.
    $( [21-Apr-1994] $)

  $( Simplification of triple conjunction. $)
  3simp3 $p |- ( ( ph /\ ps /\ ch ) -> ch ) $=
    wph wps wch w3a wps wch wph wps wch 3simpc pm3.27d $.
    $( [21-Apr-1994] $)

  ${
    3simp1i.1 $e |- ( ph /\ ps /\ ch ) $.
    $( Infer a conjunct from a triple conjunction. $)
    3simp1i $p |- ph $=
      wph wps wch w3a wph 3simp1i.1 wph wps wch 3simp1 ax-mp $.
      $( [21-Apr-2005] $) $( [19-Apr-2005] $)

    $( Infer a conjunct from a triple conjunction. $)
    3simp2i $p |- ps $=
      wph wps wch w3a wps 3simp1i.1 wph wps wch 3simp2 ax-mp $.
      $( [21-Apr-2005] $) $( [19-Apr-2005] $)

    $( Infer a conjunct from a triple conjunction. $)
    3simp3i $p |- ch $=
      wph wps wch w3a wch 3simp1i.1 wph wps wch 3simp3 ax-mp $.
      $( [21-Apr-2005] $) $( [19-Apr-2005] $)
  $}

  ${
    3simp1d.1 $e |- ( ph -> ( ps /\ ch /\ th ) ) $.
    $( Deduce a conjunct from a triple conjunction. $)
    3simp1d $p |- ( ph -> ps ) $=
      wph wps wch wth w3a wps 3simp1d.1 wps wch wth 3simp1 syl $.
      $( [6-Sep-2005] $) $( [4-Sep-2005] $)

    $( Deduce a conjunct from a triple conjunction. $)
    3simp2d $p |- ( ph -> ch ) $=
      wph wps wch wth w3a wch 3simp1d.1 wps wch wth 3simp2 syl $.
      $( [6-Sep-2005] $) $( [4-Sep-2005] $)

    $( Deduce a conjunct from a triple conjunction. $)
    3simp3d $p |- ( ph -> th ) $=
      wph wps wch wth w3a wth 3simp1d.1 wps wch wth 3simp3 syl $.
      $( [7-Sep-2005] $) $( [4-Sep-2005] $)
  $}

  ${
    3adant.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    $( Deduction adding a conjunct to antecedent. $)
    3adant1 $p |- ( ( th /\ ph /\ ps ) -> ch ) $=
      wth wph wps w3a wph wps wa wch wth wph wps 3simpc 3adant.1 syl $.
      $( [16-Jul-1995] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adant2 $p |- ( ( ph /\ th /\ ps ) -> ch ) $=
      wph wth wps w3a wph wps wa wch wph wth wps 3simpb 3adant.1 syl $.
      $( [16-Jul-1995] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adant3 $p |- ( ( ph /\ ps /\ th ) -> ch ) $=
      wph wps wth w3a wph wps wa wch wph wps wth 3simpa 3adant.1 syl $.
      $( [16-Jul-1995] $)
  $}

  ${
    3ad2ant.1 $e |- ( ph -> ch ) $.
    $( Deduction adding conjuncts to an antecedent. $)
    3ad2ant1 $p |- ( ( ph /\ ps /\ th ) -> ch ) $=
      wph wth wch wps wph wch wth 3ad2ant.1 adantr 3adant2 $.
      $( [23-Apr-2005] $) $( [21-Apr-2005] $)

    $( Deduction adding conjuncts to an antecedent. $)
    3ad2ant2 $p |- ( ( ps /\ ph /\ th ) -> ch ) $=
      wph wth wch wps wph wch wth 3ad2ant.1 adantr 3adant1 $.
      $( [23-Apr-2005] $) $( [21-Apr-2005] $)

    $( Deduction adding conjuncts to an antecedent. $)
    3ad2ant3 $p |- ( ( ps /\ th /\ ph ) -> ch ) $=
      wth wph wch wps wph wch wth 3ad2ant.1 adantl 3adant1 $.
      $( [23-Apr-2005] $) $( [21-Apr-2005] $)
  $}

  ${
    3adantl.1 $e |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $.
    $( Deduction adding a conjunct to antecedent. $)
    3adantl1 $p |- ( ( ( ta /\ ph /\ ps ) /\ ch ) -> th ) $=
      wta wph wps w3a wch wth wph wps wch wth wi wta wph wps wa wch wth
      3adantl.1 ex 3adant1 imp $.
      $( [26-Feb-2005] $) $( [24-Feb-2005] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adantl2 $p |- ( ( ( ph /\ ta /\ ps ) /\ ch ) -> th ) $=
      wph wta wps w3a wch wth wph wps wch wth wi wta wph wps wa wch wth
      3adantl.1 ex 3adant2 imp $.
      $( [25-Feb-2005] $) $( [24-Feb-2005] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adantl3 $p |- ( ( ( ph /\ ps /\ ta ) /\ ch ) -> th ) $=
      wph wps wta w3a wch wth wph wps wch wth wi wta wph wps wa wch wth
      3adantl.1 ex 3adant3 imp $.
      $( [28-Apr-2005] $) $( [24-Feb-2005] $)
  $}

  ${
    3adantr.1 $e |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $.
    $( Deduction adding a conjunct to antecedent. $)
    3adantr1 $p |- ( ( ph /\ ( ta /\ ps /\ ch ) ) -> th ) $=
      wta wps wch w3a wph wth wps wch wph wth wta wph wps wch wa wth 3adantr.1
      ancoms 3adantl1 ancoms $.
      $( [27-Jun-2005] $) $( [27-Apr-2005] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adantr2 $p |- ( ( ph /\ ( ps /\ ta /\ ch ) ) -> th ) $=
      wps wta wch w3a wph wth wps wch wph wth wta wph wps wch wa wth 3adantr.1
      ancoms 3adantl2 ancoms $.
      $( [28-Apr-2005] $) $( [27-Apr-2005] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adantr3 $p |- ( ( ph /\ ( ps /\ ch /\ ta ) ) -> th ) $=
      wps wch wta w3a wph wth wps wch wph wth wta wph wps wch wa wth 3adantr.1
      ancoms 3adantl3 ancoms $.
      $( [28-Apr-2005] $) $( [27-Apr-2005] $)
  $}

  ${
    3ad2antl.1 $e |- ( ( ph /\ ch ) -> th ) $.
    $( Deduction adding conjuncts to antecedent. $)
    3ad2antl1 $p |- ( ( ( ph /\ ps /\ ta ) /\ ch ) -> th ) $=
      wph wta wch wth wps wph wch wth wta 3ad2antl.1 adantlr 3adantl2 $.
      $( [4-Aug-2007] $) $( [4-Aug-2007] $)

    $( Deduction adding conjuncts to antecedent. $)
    3ad2antl2 $p |- ( ( ( ps /\ ph /\ ta ) /\ ch ) -> th ) $=
      wph wta wch wth wps wph wch wth wta 3ad2antl.1 adantlr 3adantl1 $.
      $( [4-Aug-2007] $) $( [4-Aug-2007] $)

    $( Deduction adding conjuncts to antecedent. $)
    3ad2antl3 $p |- ( ( ( ps /\ ta /\ ph ) /\ ch ) -> th ) $=
      wta wph wch wth wps wph wch wth wta 3ad2antl.1 adantll 3adantl1 $.
      $( [4-Aug-2007] $) $( [4-Aug-2007] $)

    $( Deduction adding a conjuncts to antecedent. $)
    3ad2antr1 $p |- ( ( ph /\ ( ch /\ ps /\ ta ) ) -> th ) $=
      wph wch wps wth wta wph wch wth wps 3ad2antl.1 adantrr 3adantr3 $.
      $( [25-Dec-2007] $) $( [25-Dec-2007] $)

    $( Deduction adding a conjuncts to antecedent. $)
    3ad2antr2 $p |- ( ( ph /\ ( ps /\ ch /\ ta ) ) -> th ) $=
      wph wps wch wth wta wph wch wth wps 3ad2antl.1 adantrl 3adantr3 $.
      $( [27-Dec-2007] $) $( [27-Dec-2007] $)

    $( Deduction adding a conjuncts to antecedent. $)
    3ad2antr3 $p |- ( ( ph /\ ( ps /\ ta /\ ch ) ) -> th ) $=
      wph wta wch wth wps wph wch wth wta 3ad2antl.1 adantrl 3adantr1 $.
      $( [30-Dec-2007] $) $( [30-Dec-2007] $)
  $}

  $( Introduction in triple disjunction. $)
  3mix1 $p |- ( ph -> ( ph \/ ps \/ ch ) ) $=
    wph wph wps wch wo wo wph wps wch w3o wph wps wch wo orc wph wps wch 3orass
    sylibr $.
    $( [4-Apr-1995] $)

  $( Introduction in triple disjunction. $)
  3mix2 $p |- ( ph -> ( ps \/ ph \/ ch ) ) $=
    wph wph wch wps w3o wps wph wch w3o wph wch wps 3mix1 wps wph wch 3orrot
    sylibr $.
    $( [4-Apr-1995] $)

  $( Introduction in triple disjunction. $)
  3mix3 $p |- ( ph -> ( ps \/ ch \/ ph ) ) $=
    wph wph wps wch w3o wps wch wph w3o wph wps wch 3mix1 wph wps wch 3orrot
    sylib $.
    $( [4-Apr-1995] $)

  ${
    3pm3.2i.1 $e |- ph $.
    3pm3.2i.2 $e |- ps $.
    3pm3.2i.3 $e |- ch $.
    $( Infer conjunction of premises. $)
    3pm3.2i $p |- ( ph /\ ps /\ ch ) $=
      wph wps wch w3a wph wps wa wch wph wps wch df-3an wph wps 3pm3.2i.1
      3pm3.2i.2 pm3.2i 3pm3.2i.3 mpbir2an $.
      $( [10-Feb-1995] $)
  $}

  ${
    3jca.1 $e |- ( ph -> ps ) $.
    3jca.2 $e |- ( ph -> ch ) $.
    3jca.3 $e |- ( ph -> th ) $.
    $( Join consequents with conjunction. $)
    3jca $p |- ( ph -> ( ps /\ ch /\ th ) ) $=
      wph wps wch wa wth wa wps wch wth w3a wph wps wch wa wth wph wps wch
      3jca.1 3jca.2 jca 3jca.3 jca wps wch wth df-3an sylibr $.
      $( [9-Apr-1994] $)
  $}

  ${
    3jcad.1 $e |- ( ph -> ( ps -> ch ) ) $.
    3jcad.2 $e |- ( ph -> ( ps -> th ) ) $.
    3jcad.3 $e |- ( ph -> ( ps -> ta ) ) $.
    $( Deduction conjoining the consequents of three implications. $)
    3jcad $p |- ( ph -> ( ps -> ( ch /\ th /\ ta ) ) ) $=
      wph wps wch wth wta w3a wph wps wa wch wth wta wph wps wch 3jcad.1 imp
      wph wps wth 3jcad.2 imp wph wps wta 3jcad.3 imp 3jca ex $.
      $( [3-Oct-2005] $) $( [25-Sep-2005] $)
  $}

  ${
    $v et $. $( Greek eta $)
    i3wet $f wff et $.
    3anim123i.1 $e |- ( ph -> ps ) $.
    3anim123i.2 $e |- ( ch -> th ) $.
    3anim123i.3 $e |- ( ta -> et ) $.
    $( Join antecedents and consequents with conjunction. $)
    3anim123i $p |- ( ( ph /\ ch /\ ta ) -> ( ps /\ th /\ et ) ) $=
      wph wch wa wta wa wps wth wa i3wet wa wph wch wta w3a wps wth i3wet w3a
      wph wch wa wps wth wa wta i3wet wph wps wch wth 3anim123i.1 3anim123i.2
      anim12i 3anim123i.3 anim12i wph wch wta df-3an wps wth i3wet df-3an
      3imtr4 $.
      $( [8-Apr-1994] $)
  $}

  ${
    $v et $. $( Greek eta $)
    b3wet $f wff et $.
    bi3.1 $e |- ( ph <-> ps ) $.
    bi3.2 $e |- ( ch <-> th ) $.
    bi3.3 $e |- ( ta <-> et ) $.
    $( Join 3 biconditionals with conjunction. $)
    3anbi123i $p |- ( ( ph /\ ch /\ ta ) <-> ( ps /\ th /\ et ) ) $=
      wph wch wa wta wa wps wth wa b3wet wa wph wch wta w3a wps wth b3wet w3a
      wph wch wa wps wth wa wta b3wet wph wps wch wth bi3.1 bi3.2 anbi12i bi3.3
      anbi12i wph wch wta df-3an wps wth b3wet df-3an 3bitr4 $.
      $( [21-Apr-1994] $)

    $( Join 3 biconditionals with disjunction. $)
    3orbi123i $p |- ( ( ph \/ ch \/ ta ) <-> ( ps \/ th \/ et ) ) $=
      wph wch wo wta wo wps wth wo b3wet wo wph wch wta w3o wps wth b3wet w3o
      wph wch wo wps wth wo wta b3wet wph wps wch wth bi3.1 bi3.2 orbi12i bi3.3
      orbi12i wph wch wta df-3or wps wth b3wet df-3or 3bitr4 $.
      $( [17-May-1994] $)
  $}

  ${
    3anbi1i.1 $e |- ( ph <-> ps ) $.
    $( Inference adding two conjuncts to each side of a biconditional. $)
    3anbi1i $p |- ( ( ph /\ ch /\ th ) <-> ( ps /\ ch /\ th ) ) $=
      wph wps wch wch wth wth 3anbi1i.1 wch pm4.2 wth pm4.2 3anbi123i $.
      $( [8-Sep-2006] $) $( [8-Sep-2006] $)

    $( Inference adding two conjuncts to each side of a biconditional. $)
    3anbi2i $p |- ( ( ch /\ ph /\ th ) <-> ( ch /\ ps /\ th ) ) $=
      wch wch wph wps wth wth wch pm4.2 3anbi1i.1 wth pm4.2 3anbi123i $.
      $( [5-Oct-2006] $) $( [8-Sep-2006] $)

    $( Inference adding two conjuncts to each side of a biconditional. $)
    3anbi3i $p |- ( ( ch /\ th /\ ph ) <-> ( ch /\ th /\ ps ) ) $=
      wch wch wth wth wph wps wch pm4.2 wth pm4.2 3anbi1i.1 3anbi123i $.
      $( [18-Oct-2006] $) $( [8-Sep-2006] $)
  $}

  ${
    3imp.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( Importation inference. $)
    3imp $p |- ( ( ph /\ ps /\ ch ) -> th ) $=
      wph wps wch w3a wph wps wa wch wa wth wph wps wch df-3an wph wps wch wth
      3imp.1 imp31 sylbi $.
      $( [8-Apr-1994] $)
  $}

  ${
    3impa.1 $e |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $.
    $( Importation from double to triple conjunction. $)
    3impa $p |- ( ( ph /\ ps /\ ch ) -> th ) $=
      wph wps wch wth wph wps wch wth 3impa.1 exp31 3imp $.
      $( [20-Aug-1995] $)
  $}

  ${
    3impb.1 $e |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $.
    $( Importation from double to triple conjunction. $)
    3impb $p |- ( ( ph /\ ps /\ ch ) -> th ) $=
      wph wps wch wth wph wps wch wth 3impb.1 exp32 3imp $.
      $( [20-Aug-1995] $)
  $}

  ${
    3impia.1 $e |- ( ( ph /\ ps ) -> ( ch -> th ) ) $.
    $( Importation to triple conjunction. $)
    3impia $p |- ( ( ph /\ ps /\ ch ) -> th ) $=
      wph wps wch wth wph wps wch wth wi 3impia.1 ex 3imp $.
      $( [13-Jun-2006] $) $( [13-Jun-2006] $)
  $}

  ${
    3impib.1 $e |- ( ph -> ( ( ps /\ ch ) -> th ) ) $.
    $( Importation to triple conjunction. $)
    3impib $p |- ( ( ph /\ ps /\ ch ) -> th ) $=
      wph wps wch wth wph wps wch wth 3impib.1 exp3a 3imp $.
      $( [15-Jun-2006] $) $( [13-Jun-2006] $)
  $}

  ${
    3exp.1 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( Exportation inference. $)
    3exp $p |- ( ph -> ( ps -> ( ch -> th ) ) ) $=
      wph wps wch wth wph wps wa wch wa wph wps wch w3a wth wph wps wch df-3an
      3exp.1 sylbir exp31 $.
      $( [30-May-1994] $)

    $( Exportation from triple to double conjunction. $)
    3expa $p |- ( ( ( ph /\ ps ) /\ ch ) -> th ) $=
      wph wps wch wth wph wps wch wth 3exp.1 3exp imp31 $.
      $( [20-Aug-1995] $)

    $( Exportation from triple to double conjunction. $)
    3expb $p |- ( ( ph /\ ( ps /\ ch ) ) -> th ) $=
      wph wps wch wth wph wps wch wth 3exp.1 3exp imp32 $.
      $( [20-Aug-1995] $)

    $( Exportation from triple conjunction. $)
    3expia $p |- ( ( ph /\ ps ) -> ( ch -> th ) ) $=
      wph wps wch wth wi wph wps wch wth 3exp.1 3exp imp $.
      $( [19-May-2007] $) $( [19-May-2007] $)

    $( Exportation from triple conjunction. $)
    3expib $p |- ( ph -> ( ( ps /\ ch ) -> th ) ) $=
      wph wps wch wth wph wps wch wth 3exp.1 3exp imp3a $.
      $( [20-May-2007] $) $( [19-May-2007] $)

    $( Commutation in antecedent.  Swap 1st and 3rd. $)
    3com12 $p |- ( ( ps /\ ph /\ ch ) -> th ) $=
      wps wph wch wth wph wps wch wth wi wph wps wch wth 3exp.1 3exp com12 3imp
      $.
      $( [28-Jan-1996] $)

    $( Commutation in antecedent.  Swap 1st and 3rd. $)
    3com13 $p |- ( ( ch /\ ps /\ ph ) -> th ) $=
      wch wps wph w3a wph wps wch w3a wth wch wps wph 3anrev 3exp.1 sylbi $.
      $( [28-Jan-1996] $)

    $( Commutation in antecedent.  Swap 2nd and 3rd. $)
    3com23 $p |- ( ( ph /\ ch /\ ps ) -> th ) $=
      wph wch wps wth wph wps wch wth wph wps wch wth 3exp.1 3exp com23 3imp $.
      $( [28-Jan-1996] $)

    $( Commutation in antecedent.  Rotate left. $)
    3coml $p |- ( ( ps /\ ch /\ ph ) -> th ) $=
      wph wch wps wth wph wps wch wth 3exp.1 3com23 3com13 $.
      $( [28-Jan-1996] $)

    $( Commutation in antecedent.  Rotate right. $)
    3comr $p |- ( ( ch /\ ph /\ ps ) -> th ) $=
      wps wch wph wth wph wps wch wth 3exp.1 3coml 3coml $.
      $( [28-Jan-1996] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adant3r1 $p |- ( ( ph /\ ( ta /\ ps /\ ch ) ) -> th ) $=
      wph wps wch wth wta wph wps wch wth 3exp.1 3expb 3adantr1 $.
      $( [16-Feb-2008] $) $( [16-Feb-2008] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adant3r2 $p |- ( ( ph /\ ( ps /\ ta /\ ch ) ) -> th ) $=
      wph wps wch wth wta wph wps wch wth 3exp.1 3expb 3adantr2 $.
      $( [17-Feb-2008] $) $( [17-Feb-2008] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adant3r3 $p |- ( ( ph /\ ( ps /\ ch /\ ta ) ) -> th ) $=
      wph wps wch wth wta wph wps wch wth 3exp.1 3expb 3adantr3 $.
      $( [18-Feb-2008] $) $( [18-Feb-2008] $)
  $}

  ${
    3an1rs.1 $e |- ( ( ( ph /\ ps /\ ch ) /\ th ) -> ta ) $.
  $}

  ${
    3imp1.1 $e |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $.
    $( Importation to left triple conjunction. $)
    3imp1 $p |- ( ( ( ph /\ ps /\ ch ) /\ th ) -> ta ) $=
      wph wps wch w3a wth wta wph wps wch wth wta wi 3imp1.1 3imp imp $.
      $( [26-Feb-2005] $) $( [24-Feb-2005] $)

    $( Importation deduction for triple conjunction. $)
    3impd $p |- ( ph -> ( ( ps /\ ch /\ th ) -> ta ) ) $=
      wps wch wth w3a wph wta wps wch wth wph wta wi wph wps wch wth wta
      3imp1.1 com4l 3imp com12 $.
      $( [28-Oct-2006] $) $( [26-Oct-2006] $)

    $( Importation to right triple conjunction. $)
    3imp2 $p |- ( ( ph /\ ( ps /\ ch /\ th ) ) -> ta ) $=
      wph wps wch wth w3a wta wph wps wch wth wta 3imp1.1 3impd imp $.
      $( [28-Oct-2006] $) $( [26-Oct-2006] $)
  $}

  ${
    3exp1.1 $e |- ( ( ( ph /\ ps /\ ch ) /\ th ) -> ta ) $.
    $( Exportation from left triple conjunction. $)
    3exp1 $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wph wps wch wth wta wi wph wps wch w3a wth wta 3exp1.1 ex 3exp $.
      $( [26-Feb-2005] $) $( [24-Feb-2005] $)
  $}

  ${
    3expd.1 $e |- ( ph -> ( ( ps /\ ch /\ th ) -> ta ) ) $.
    $( Exportation deduction for triple conjunction. $)
    3expd $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wps wch wth wph wta wps wch wth wph wta wi wph wps wch wth w3a wta
      3expd.1 com12 3exp com4r $.
      $( [27-Oct-2006] $) $( [26-Oct-2006] $)
  $}

  ${
    3exp2.1 $e |- ( ( ph /\ ( ps /\ ch /\ th ) ) -> ta ) $.
    $( Exportation from right triple conjunction. $)
    3exp2 $p |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $=
      wph wps wch wth wta wph wps wch wth w3a wta 3exp2.1 ex 3expd $.
      $( [28-Oct-2006] $) $( [26-Oct-2006] $)
  $}

  ${
    3adant1l.1 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( Deduction adding a conjunct to antecedent. $)
    3adant1l $p |- ( ( ( ta /\ ph ) /\ ps /\ ch ) -> th ) $=
      wta wph wa wps wch wth wph wps wch wa wth wta wph wps wch wth 3adant1l.1
      3expb adantll 3impb $.
      $( [12-Jan-2006] $) $( [8-Jan-2006] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adant1r $p |- ( ( ( ph /\ ta ) /\ ps /\ ch ) -> th ) $=
      wph wta wa wps wch wth wph wps wch wa wth wta wph wps wch wth 3adant1l.1
      3expb adantlr 3impb $.
      $( [17-Jan-2006] $) $( [8-Jan-2006] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adant2l $p |- ( ( ph /\ ( ta /\ ps ) /\ ch ) -> th ) $=
      wta wps wa wph wch wth wps wph wch wth wta wph wps wch wth 3adant1l.1
      3com12 3adant1l 3com12 $.
      $( [22-Feb-2006] $) $( [8-Jan-2006] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adant2r $p |- ( ( ph /\ ( ps /\ ta ) /\ ch ) -> th ) $=
      wps wta wa wph wch wth wps wph wch wth wta wph wps wch wth 3adant1l.1
      3com12 3adant1r 3com12 $.
      $( [23-Jan-2006] $) $( [8-Jan-2006] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adant3l $p |- ( ( ph /\ ps /\ ( ta /\ ch ) ) -> th ) $=
      wta wch wa wps wph wth wch wps wph wth wta wph wps wch wth 3adant1l.1
      3com13 3adant1l 3com13 $.
      $( [5-Feb-2006] $) $( [8-Jan-2006] $)

    $( Deduction adding a conjunct to antecedent. $)
    3adant3r $p |- ( ( ph /\ ps /\ ( ch /\ ta ) ) -> th ) $=
      wch wta wa wps wph wth wch wps wph wth wta wph wps wch wth 3adant1l.1
      3com13 3adant1r 3com13 $.
      $( [27-Jan-2006] $) $( [8-Jan-2006] $)
  $}

  ${
    syl3anc.1 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    syl3anc.2 $e |- ( ta -> ph ) $.
    syl3anc.3 $e |- ( ta -> ps ) $.
    syl3anc.4 $e |- ( ta -> ch ) $.
    $( A syllogism inference combined with contraction. $)
    syl3anc $p |- ( ta -> th ) $=
      wta wph wps wch w3a wth wta wph wps wch syl3anc.2 syl3anc.3 syl3anc.4
      3jca syl3anc.1 syl $.
      $( [2-Jan-2005] $) $( [1-Jan-2005] $)
  $}

  ${
    $v et $. $( Greek eta $)
    $v ze $. $( Greek zeta $)
    syl3an.we $f wff et $.
    syl3an.wz $f wff ze $.
    syl3an.1 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    ${
      syl3an1.2 $e |- ( ta -> ph ) $.
      $( A syllogism inference. $)
      syl3an1 $p |- ( ( ta /\ ps /\ ch ) -> th ) $=
        wta wps wch wth wph wps wch wa wth wta wph wps wch wth syl3an.1 3expb
        syl3an1.2 sylan 3impb $.
        $( [22-Aug-1995] $)
    $}

    ${
      syl3an2.2 $e |- ( ta -> ps ) $.
      $( A syllogism inference. $)
      syl3an2 $p |- ( ( ph /\ ta /\ ch ) -> th ) $=
        wph wta wch wth wph wps wch wth wi wta wph wps wch wth syl3an.1 3exp
        syl3an2.2 syl5 3imp $.
        $( [22-Aug-1995] $)
    $}

    ${
      syl3an3.2 $e |- ( ta -> ch ) $.
      $( A syllogism inference. $)
      syl3an3 $p |- ( ( ph /\ ps /\ ta ) -> th ) $=
        wph wps wta wth wph wps wch wth wta wph wps wch wth syl3an.1 3exp
        syl3an3.2 syl7 3imp $.
        $( [22-Aug-1995] $)
    $}

    ${
      syl3an1b.2 $e |- ( ta <-> ph ) $.
      $( A syllogism inference. $)
      syl3an1b $p |- ( ( ta /\ ps /\ ch ) -> th ) $=
        wph wps wch wth wta syl3an.1 wta wph syl3an1b.2 biimp syl3an1 $.
        $( [22-Aug-1995] $)
    $}

    ${
      syl3an2b.2 $e |- ( ta <-> ps ) $.
      $( A syllogism inference. $)
      syl3an2b $p |- ( ( ph /\ ta /\ ch ) -> th ) $=
        wph wps wch wth wta syl3an.1 wta wps syl3an2b.2 biimp syl3an2 $.
        $( [22-Aug-1995] $)
    $}

    ${
      syl3an3b.2 $e |- ( ta <-> ch ) $.
      $( A syllogism inference. $)
      syl3an3b $p |- ( ( ph /\ ps /\ ta ) -> th ) $=
        wph wps wch wth wta syl3an.1 wta wch syl3an3b.2 biimp syl3an3 $.
        $( [22-Aug-1995] $)
    $}

    ${
      syl3an1br.2 $e |- ( ph <-> ta ) $.
      $( A syllogism inference. $)
      syl3an1br $p |- ( ( ta /\ ps /\ ch ) -> th ) $=
        wph wps wch wth wta syl3an.1 wph wta syl3an1br.2 biimpr syl3an1 $.
        $( [22-Aug-1995] $)
    $}

    ${
      syl3an2br.2 $e |- ( ps <-> ta ) $.
      $( A syllogism inference. $)
      syl3an2br $p |- ( ( ph /\ ta /\ ch ) -> th ) $=
        wph wps wch wth wta syl3an.1 wps wta syl3an2br.2 biimpr syl3an2 $.
        $( [22-Aug-1995] $)
    $}

    ${
      syl3an3br.2 $e |- ( ch <-> ta ) $.
      $( A syllogism inference. $)
      syl3an3br $p |- ( ( ph /\ ps /\ ta ) -> th ) $=
        wph wps wch wth wta syl3an.1 wch wta syl3an3br.2 biimpr syl3an3 $.
        $( [22-Aug-1995] $)
    $}

    ${
      syl3an.2 $e |- ( ta -> ph ) $.
      syl3an.3 $e |- ( et -> ps ) $.
      syl3an.4 $e |- ( ze -> ch ) $.
      $( A triple syllogism inference. $)
      syl3an $p |- ( ( ta /\ et /\ ze ) -> th ) $=
        wta syl3an.we syl3an.wz w3a wph wps wch w3a wth wta wph syl3an.we wps
        syl3an.wz wch syl3an.2 syl3an.3 syl3an.4 3anim123i syl3an.1 syl $.
        $( [14-May-2004] $) $( [13-May-2004] $)
    $}

    ${
      syl3anb.2 $e |- ( ta <-> ph ) $.
      syl3anb.3 $e |- ( et <-> ps ) $.
      syl3anb.4 $e |- ( ze <-> ch ) $.
      $( A triple syllogism inference. $)
      syl3anb $p |- ( ( ta /\ et /\ ze ) -> th ) $=
        wta syl3an.we syl3an.wz w3a wph wps wch w3a wth wta wph syl3an.we wps
        syl3an.wz wch syl3anb.2 syl3anb.3 syl3anb.4 3anbi123i syl3an.1 sylbi $.
        $( [20-Oct-2005] $) $( [15-Oct-2005] $)
    $}

    ${
      syl3dan3.2 $e |- ( ( ph /\ ps /\ ta ) -> ch ) $.
      $( A syllogism inference. $)
      syl3dan3 $p |- ( ( ph /\ ps /\ ta ) -> th ) $=
        wph wps wch wth wph wps wta w3a syl3an.1 wph wps wta 3simp1 wph wps wta
        3simp2 syl3dan3.2 syl3anc $.
        $( [23-May-2007] $) $( [20-May-2007] $)
    $}

    ${
      syl3dan2.2 $e |- ( ( ph /\ ta /\ ch ) -> ps ) $.
      $( A syllogism inference. $)
      syl3dan2 $p |- ( ( ph /\ ta /\ ch ) -> th ) $=
        wph wch wta wth wph wch wps wth wta wph wps wch wth syl3an.1 3com23 wph
        wta wch wps syl3dan2.2 3com23 syl3dan3 3com23 $.
        $( [24-May-2007] $) $( [20-May-2007] $)
    $}
  $}

  ${
    $v et $. $( Greek eta $)
    $v ze $. $( Greek zeta $)
    $v si $. $( Greek sigma $)
    syl3anl1.we $f wff et $.
    syl3anl1.wz $f wff ze $.
    syl3anl1.ws $f wff si $.
    syl3anl1.1 $e |- ( ( ( ph /\ ps /\ ch ) /\ th ) -> ta ) $.
    ${
      syl3anl1.2 $e |- ( et -> ph ) $.
      $( A syllogism inference. $)
      syl3anl1 $p |- ( ( ( et /\ ps /\ ch ) /\ th ) -> ta ) $=
        syl3anl1.we wps wch w3a wth wta wph wps wch wth wta wi syl3anl1.we wph
        wps wch w3a wth wta syl3anl1.1 ex syl3anl1.2 syl3an1 imp $.
        $( [28-Apr-2005] $) $( [24-Feb-2005] $)
    $}

    ${
      syl3anl2.2 $e |- ( et -> ps ) $.
      $( A syllogism inference. $)
      syl3anl2 $p |- ( ( ( ph /\ et /\ ch ) /\ th ) -> ta ) $=
        wph syl3anl1.we wch w3a wth wta wph wps wch wth wta wi syl3anl1.we wph
        wps wch w3a wth wta syl3anl1.1 ex syl3anl2.2 syl3an2 imp $.
        $( [26-Feb-2005] $) $( [24-Feb-2005] $)
    $}

    ${
      syl3anl3.2 $e |- ( et -> ch ) $.
      $( A syllogism inference. $)
      syl3anl3 $p |- ( ( ( ph /\ ps /\ et ) /\ th ) -> ta ) $=
        wph wps syl3anl1.we w3a wth wta wph wps wch wth wta wi syl3anl1.we wph
        wps wch w3a wth wta syl3anl1.1 ex syl3anl3.2 syl3an3 imp $.
        $( [27-Jun-2005] $) $( [24-Feb-2005] $)
    $}

    ${
      syl3anl.2 $e |- ( et -> ph ) $.
      syl3anl.3 $e |- ( ze -> ps ) $.
      syl3anl.4 $e |- ( si -> ch ) $.
      $( A triple syllogism inference. $)
      syl3anl $p |- ( ( ( et /\ ze /\ si ) /\ th ) -> ta ) $=
        wph wps wch w3a wth wta syl3anl1.we syl3anl1.wz syl3anl1.ws w3a
        syl3anl1.1 syl3anl1.we wph syl3anl1.wz wps syl3anl1.ws wch syl3anl.2
        syl3anl.3 syl3anl.4 3anim123i sylan $.
        $( [24-Dec-2006] $) $( [24-Dec-2006] $)
    $}
  $}

  ${
    $v et $. $( Greek eta $)
    $v ze $. $( Greek zeta $)
    $v si $. $( Greek sigma $)
    syl3anr1.we $f wff et $.
    syl3anr1.1 $e |- ( ( ph /\ ( ps /\ ch /\ th ) ) -> ta ) $.
    ${
      syl3anr1.2 $e |- ( et -> ps ) $.
      $( A syllogism inference. $)
      syl3anr1 $p |- ( ( ph /\ ( et /\ ch /\ th ) ) -> ta ) $=
        syl3anr1.we wch wth w3a wph wta wps wch wth wph wta syl3anr1.we wph wps
        wch wth w3a wta syl3anr1.1 ancoms syl3anr1.2 syl3anl1 ancoms $.
        $( [16-Aug-2007] $) $( [31-Jul-2007] $)
    $}

    ${
      syl3anr2.2 $e |- ( et -> ch ) $.
      $( A syllogism inference. $)
      syl3anr2 $p |- ( ( ph /\ ( ps /\ et /\ th ) ) -> ta ) $=
        wps syl3anr1.we wth w3a wph wta wps wch wth wph wta syl3anr1.we wph wps
        wch wth w3a wta syl3anr1.1 ancoms syl3anr2.2 syl3anl2 ancoms $.
        $( [6-Aug-2007] $) $( [1-Aug-2007] $)
    $}

    ${
      syl3anr3.2 $e |- ( et -> th ) $.
      $( A syllogism inference. $)
      syl3anr3 $p |- ( ( ph /\ ( ps /\ ch /\ et ) ) -> ta ) $=
        wps wch syl3anr1.we w3a wph wta wps wch wth wph wta syl3anr1.we wph wps
        wch wth w3a wta syl3anr1.1 ancoms syl3anr3.2 syl3anl3 ancoms $.
        $( [23-Aug-2007] $) $( [23-Aug-2007] $)
    $}
  $}

  ${
    3impdi.1 $e |- ( ( ( ph /\ ps ) /\ ( ph /\ ch ) ) -> th ) $.
    $( Importation inference (undistribute conjunction). $)
    3impdi $p |- ( ( ph /\ ps /\ ch ) -> th ) $=
      wph wps wch wth wph wps wch wth 3impdi.1 anandis 3impb $.
      $( [14-Aug-1995] $)
  $}

  ${
    3impdir.1 $e |- ( ( ( ph /\ ps ) /\ ( ch /\ ps ) ) -> th ) $.
    $( Importation inference (undistribute conjunction). $)
    3impdir $p |- ( ( ph /\ ch /\ ps ) -> th ) $=
      wph wch wps wth wph wch wps wth 3impdir.1 anandirs 3impa $.
      $( [20-Aug-1995] $)
  $}

  ${
    3anidm12.1 $e |- ( ( ph /\ ph /\ ps ) -> ch ) $.
    $( Inference from idempotent law for conjunction. $)
    3anidm12 $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wch wph wps wch wi wph wph wps wch 3anidm12.1 3exp pm2.43i imp $.
      $( [7-Mar-2008] $) $( [7-Mar-2008] $)
  $}

  ${
    3anidm13.1 $e |- ( ( ph /\ ps /\ ph ) -> ch ) $.
    $( Inference from idempotent law for conjunction. $)
    3anidm13 $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wch wph wps wph wch 3anidm13.1 3com23 3anidm12 $.
      $( [10-Mar-2008] $) $( [7-Mar-2008] $)
  $}

  ${
    3anidm23.1 $e |- ( ( ph /\ ps /\ ps ) -> ch ) $.
    $( Inference from idempotent law for conjunction. $)
    3anidm23 $p |- ( ( ph /\ ps ) -> ch ) $=
      wph wps wch wph wps wch wph wps wps wch 3anidm23.1 3exp pm2.43d imp $.
      $( [1-Feb-2007] $) $( [1-Feb-2007] $)
  $}

  ${
    3ori.1 $e |- ( ph \/ ps \/ ch ) $.
    $( Infer implication from triple disjunction. $)
    3ori $p |- ( ( -. ph /\ -. ps ) -> ch ) $=
      wph wn wps wn wa wph wps wo wn wch wph wps ioran wph wps wo wch wph wps
      wch w3o wph wps wo wch wo 3ori.1 wph wps wch df-3or mpbi ori sylbir $.
      $( [28-Sep-2006] $) $( [26-Sep-2006] $)
  $}

  $( Disjunction of 3 antecedents. $)
  3jao $p |- ( ( ( ph -> ps ) /\ ( ch -> ps ) /\ ( th -> ps ) ) ->
              ( ( ph \/ ch \/ th ) -> ps ) ) $=
    wph wps wi wch wps wi wth wps wi w3a wph wch wo wth wo wps wph wch wth w3o
    wph wps wi wch wps wi wth wps wi wph wch wo wth wo wps wi wph wps wi wch
    wps wi wph wch wo wps wi wth wps wi wph wch wo wth wo wps wi wi wph wps wch
    jao wph wch wo wps wth jao syl6 3imp wph wch wth df-3or syl5ib $.
    $( [8-Apr-1994] $)

  ${
    3jaoi.1 $e |- ( ph -> ps ) $.
    3jaoi.2 $e |- ( ch -> ps ) $.
    3jaoi.3 $e |- ( th -> ps ) $.
    $( Disjunction of 3 antecedents (inference). $)
    3jaoi $p |- ( ( ph \/ ch \/ th ) -> ps ) $=
      wph wps wi wch wps wi wth wps wi w3a wph wch wth w3o wps wi wph wps wi
      wch wps wi wth wps wi 3jaoi.1 3jaoi.2 3jaoi.3 3pm3.2i wph wps wch wth
      3jao ax-mp $.
      $( [12-Sep-1995] $)
  $}

  ${
    3jaod.1 $e |- ( ph -> ( ps -> ch ) ) $.
    3jaod.2 $e |- ( ph -> ( th -> ch ) ) $.
    3jaod.3 $e |- ( ph -> ( ta -> ch ) ) $.
    $( Disjunction of 3 antecedents (deduction). $)
    3jaod $p |- ( ph -> ( ( ps \/ th \/ ta ) -> ch ) ) $=
      wps wch wi wth wch wi wta wch wi wps wth wta w3o wch wi wph wps wch wth
      wta 3jao 3jaod.1 3jaod.2 3jaod.3 syl3anc $.
      $( [16-Oct-2005] $) $( [14-Oct-2005] $)
  $}

  ${
    3jaoian.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    3jaoian.2 $e |- ( ( th /\ ps ) -> ch ) $.
    3jaoian.3 $e |- ( ( ta /\ ps ) -> ch ) $.
    $( Disjunction of 3 antecedents (inference). $)
    3jaoian $p |- ( ( ( ph \/ th \/ ta ) /\ ps ) -> ch ) $=
      wph wth wta w3o wps wch wph wps wch wi wth wta wph wps wch 3jaoian.1 ex
      wth wps wch 3jaoian.2 ex wta wps wch 3jaoian.3 ex 3jaoi imp $.
      $( [17-Oct-2005] $) $( [14-Oct-2005] $)
  $}

  ${
    3jaodan.1 $e |- ( ( ph /\ ps ) -> ch ) $.
    3jaodan.2 $e |- ( ( ph /\ th ) -> ch ) $.
    3jaodan.3 $e |- ( ( ph /\ ta ) -> ch ) $.
    $( Disjunction of 3 antecedents (deduction). $)
    3jaodan $p |- ( ( ph /\ ( ps \/ th \/ ta ) ) -> ch ) $=
      wph wps wth wta w3o wch wph wps wch wth wta wph wps wch 3jaodan.1 ex wph
      wth wch 3jaodan.2 ex wph wta wch 3jaodan.3 ex 3jaod imp $.
      $( [21-Oct-2005] $) $( [14-Oct-2005] $)
  $}

  ${
    $v et $. $( Greek eta $)
    $v ze $. $( Greek zeta $)
    syl3an9b.we $f wff et $.
    syl3an9b.wz $f wff ze $.
    syl3an9b.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    syl3an9b.2 $e |- ( th -> ( ch <-> ta ) ) $.
    syl3an9b.3 $e |- ( et -> ( ta <-> ze ) ) $.
    $( Nested syllogism inference conjoining 3 dissimilar antecedents. $)
    syl3an9b $p |- ( ( ph /\ th /\ et ) -> ( ps <-> ze ) ) $=
      wph wth syl3an9b.we wps syl3an9b.wz wb wph wth wa wps wta syl3an9b.we
      syl3an9b.wz wph wps wch wth wta syl3an9b.1 syl3an9b.2 sylan9bb syl3an9b.3
      sylan9bb 3impa $.
      $( [1-May-1995] $)
  $}

  ${
    $v et $. $( Greek eta $)
    $v ze $. $( Greek zeta $)
    bi3d.we $f wff et $.
    bi3d.wz $f wff ze $.
    bi3d.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    bi3d.2 $e |- ( ph -> ( th <-> ta ) ) $.
    bi3d.3 $e |- ( ph -> ( et <-> ze ) ) $.
    $( Deduction joining 3 equivalences to form equivalence of disjunctions. $)
    3orbi123d $p |- ( ph -> ( ( ps \/ th \/ et ) <-> ( ch \/ ta \/ ze ) ) ) $=
      wph wps wth wo bi3d.we wo wch wta wo bi3d.wz wo wps wth bi3d.we w3o wch
      wta bi3d.wz w3o wph wps wth wo wch wta wo bi3d.we bi3d.wz wph wps wch wth
      wta bi3d.1 bi3d.2 orbi12d bi3d.3 orbi12d wps wth bi3d.we df-3or wch wta
      bi3d.wz df-3or 3bitr4g $.
      $( [20-Apr-1994] $)

    $( Deduction joining 3 equivalences to form equivalence of conjunctions. $)
    3anbi123d $p |- ( ph -> ( ( ps /\ th /\ et ) <-> ( ch /\ ta /\ ze ) ) ) $=
      wph wps wth wa bi3d.we wa wch wta wa bi3d.wz wa wps wth bi3d.we w3a wch
      wta bi3d.wz w3a wph wps wth wa wch wta wa bi3d.we bi3d.wz wph wps wch wth
      wta bi3d.1 bi3d.2 anbi12d bi3d.3 anbi12d wps wth bi3d.we df-3an wch wta
      bi3d.wz df-3an 3bitr4g $.
      $( [22-Apr-1994] $)
  $}

  ${
    $v et $. $( Greek eta $)
    3anbi12d.we $f wff et $.
    3anbi12d.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    3anbi12d.2 $e |- ( ph -> ( th <-> ta ) ) $.
    $( Deduction conjoining and adding a conjunct to equivalences. $)
    3anbi12d $p |- ( ph -> ( ( ps /\ th /\ et ) <-> ( ch /\ ta /\ et ) ) ) $=
      wph wps wch wth wta 3anbi12d.we 3anbi12d.we 3anbi12d.1 3anbi12d.2 wph
      3anbi12d.we pm4.2i 3anbi123d $.
      $( [8-Sep-2006] $) $( [8-Sep-2006] $)

    $( Deduction conjoining and adding a conjunct to equivalences. $)
    3anbi13d $p |- ( ph -> ( ( ps /\ et /\ th ) <-> ( ch /\ et /\ ta ) ) ) $=
      wph wps wch 3anbi12d.we 3anbi12d.we wth wta 3anbi12d.1 wph 3anbi12d.we
      pm4.2i 3anbi12d.2 3anbi123d $.
      $( [9-Sep-2006] $) $( [8-Sep-2006] $)

    $( Deduction conjoining and adding a conjunct to equivalences. $)
    3anbi23d $p |- ( ph -> ( ( et /\ ps /\ th ) <-> ( et /\ ch /\ ta ) ) ) $=
      wph 3anbi12d.we 3anbi12d.we wps wch wth wta wph 3anbi12d.we pm4.2i
      3anbi12d.1 3anbi12d.2 3anbi123d $.
      $( [10-Sep-2006] $) $( [8-Sep-2006] $)
  $}

  ${
    3anbi1d.1 $e |- ( ph -> ( ps <-> ch ) ) $.
    $( Deduction adding conjuncts to an equivalence. $)
    3anbi1d $p |- ( ph -> ( ( ps /\ th /\ ta ) <-> ( ch /\ th /\ ta ) ) ) $=
      wph wps wch wth wth wta 3anbi1d.1 wph wth pm4.2i 3anbi12d $.
      $( [9-Sep-2006] $) $( [8-Sep-2006] $)

    $( Deduction adding conjuncts to an equivalence. $)
    3anbi2d $p |- ( ph -> ( ( th /\ ps /\ ta ) <-> ( th /\ ch /\ ta ) ) ) $=
      wph wth wth wps wch wta wph wth pm4.2i 3anbi1d.1 3anbi12d $.
      $( [2-Nov-2006] $) $( [8-Sep-2006] $)

    $( Deduction adding conjuncts to an equivalence. $)
    3anbi3d $p |- ( ph -> ( ( th /\ ta /\ ps ) <-> ( th /\ ta /\ ch ) ) ) $=
      wph wth wth wps wch wta wph wth pm4.2i 3anbi1d.1 3anbi13d $.
      $( [11-Sep-2006] $) $( [8-Sep-2006] $)
  $}

  ${
    $v et $. $( Greek eta $)
    $v ze $. $( Greek zeta $)
    3anim123d.we $f wff et $.
    3anim123d.wz $f wff ze $.
    3anim123d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    3anim123d.2 $e |- ( ph -> ( th -> ta ) ) $.
    3anim123d.3 $e |- ( ph -> ( et -> ze ) ) $.
    $( Deduction joining 3 implications to form implication of conjunctions. $)
    3anim123d $p |- ( ph -> ( ( ps /\ th /\ et ) -> ( ch /\ ta /\ ze ) ) ) $=
      wph wps wth wa 3anim123d.we wa wch wta wa 3anim123d.wz wa wps wth
      3anim123d.we w3a wch wta 3anim123d.wz w3a wph wps wth wa wch wta wa
      3anim123d.we 3anim123d.wz wph wps wch wth wta 3anim123d.1 3anim123d.2
      anim12d 3anim123d.3 anim12d wps wth 3anim123d.we df-3an wch wta
      3anim123d.wz df-3an 3imtr4g $.
      $( [30-Jun-2005] $) $( [24-Feb-2005] $)

    $( Deduction joining 3 implications to form implication of disjunctions. $)
    3orim123d $p |- ( ph -> ( ( ps \/ th \/ et ) -> ( ch \/ ta \/ ze ) ) ) $=
      wph wps wth wo 3anim123d.we wo wch wta wo 3anim123d.wz wo wps wth
      3anim123d.we w3o wch wta 3anim123d.wz w3o wph wps wth wo wch wta wo
      3anim123d.we 3anim123d.wz wph wps wch wth wta 3anim123d.1 3anim123d.2
      orim12d 3anim123d.3 orim12d wps wth 3anim123d.we df-3or wch wta
      3anim123d.wz df-3or 3imtr4g $.
      $( [4-Apr-1997] $)
  $}

  ${
    $v et $. $( Greek eta $)
    an6wet $f wff et $.
    $( Rearrangement of 6 conjuncts. $)
    an6 $p |- ( ( ( ph /\ ps /\ ch ) /\ ( th /\ ta /\ et ) ) <->
              ( ( ph /\ th ) /\ ( ps /\ ta ) /\ ( ch /\ et ) ) ) $=
      wph wps wch w3a wth wta an6wet w3a wa wph wth wa wps wta wa wa wch an6wet
      wa wa wph wth wa wps wta wa wch an6wet wa w3a wph wps wch w3a wth wta
      an6wet w3a wa wph wps wa wch wa wth wta wa an6wet wa wa wph wps wa wth
      wta wa wa wch an6wet wa wa wph wth wa wps wta wa wa wch an6wet wa wa wph
      wps wch w3a wph wps wa wch wa wth wta an6wet w3a wth wta wa an6wet wa wph
      wps wch df-3an wth wta an6wet df-3an anbi12i wph wps wa wch wth wta wa
      an6wet an4 wph wps wa wth wta wa wa wph wth wa wps wta wa wa wch an6wet
      wa wph wps wth wta an4 anbi1i 3bitr wph wth wa wps wta wa wch an6wet wa
      df-3an bitr4 $.
      $( [13-Mar-1995] $)
  $}

  ${
    mp3an1.1 $e |- ph $.
    mp3an1.2 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mp3an1 $p |- ( ( ps /\ ch ) -> th ) $=
      wph wps wch wa wth mp3an1.1 wph wps wch wth mp3an1.2 3expb mpan $.
      $( [21-Nov-1994] $)
  $}

  ${
    mp3an2.1 $e |- ps $.
    mp3an2.2 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mp3an2 $p |- ( ( ph /\ ch ) -> th ) $=
      wph wps wch wth mp3an2.1 wph wps wch wth mp3an2.2 3expa mpanl2 $.
      $( [21-Nov-1994] $)
  $}

  ${
    mp3an3.1 $e |- ch $.
    mp3an3.2 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mp3an3 $p |- ( ( ph /\ ps ) -> th ) $=
      wph wps wa wch wth mp3an3.1 wph wps wch wth mp3an3.2 3expa mpan2 $.
      $( [21-Nov-1994] $)
  $}

  ${
    mp3an12.1 $e |- ph $.
    mp3an12.2 $e |- ps $.
    mp3an12.3 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mp3an12 $p |- ( ch -> th ) $=
      wps wch wth mp3an12.2 wph wps wch wth mp3an12.1 mp3an12.3 mp3an1 mpan $.
      $( [15-Jul-2005] $) $( [13-Jul-2005] $)
  $}

  ${
    mp3an13.1 $e |- ph $.
    mp3an13.2 $e |- ch $.
    mp3an13.3 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mp3an13 $p |- ( ps -> th ) $=
      wph wps wth mp3an13.1 wph wps wch wth mp3an13.2 mp3an13.3 mp3an3 mpan $.
      $( [16-Jul-2005] $) $( [14-Jul-2005] $)
  $}

  ${
    mp3an23.1 $e |- ps $.
    mp3an23.2 $e |- ch $.
    mp3an23.3 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mp3an23 $p |- ( ph -> th ) $=
      wph wps wth mp3an23.1 wph wps wch wth mp3an23.2 mp3an23.3 mp3an3 mpan2 $.
      $( [16-Jul-2005] $) $( [14-Jul-2005] $)
  $}

  ${
    mp3an1i.1 $e |- ps $.
    mp3an1i.2 $e |- ( ph -> ( ( ps /\ ch /\ th ) -> ta ) ) $.
    $( An inference based on modus ponens. $)
    mp3an1i $p |- ( ph -> ( ( ch /\ th ) -> ta ) ) $=
      wch wth wa wph wta wps wch wth wph wta wi mp3an1i.1 wph wps wch wth w3a
      wta mp3an1i.2 com12 mp3an1 com12 $.
      $( [9-Jul-2005] $) $( [5-Jul-2005] $)
  $}

  ${
    mp3anl1.1 $e |- ph $.
    mp3anl1.2 $e |- ( ( ( ph /\ ps /\ ch ) /\ th ) -> ta ) $.
    $( An inference based on modus ponens. $)
    mp3anl1 $p |- ( ( ( ps /\ ch ) /\ th ) -> ta ) $=
      wps wch wa wth wta wph wps wch wth wta wi mp3anl1.1 wph wps wch w3a wth
      wta mp3anl1.2 ex mp3an1 imp $.
      $( [25-Feb-2005] $) $( [24-Feb-2005] $)
  $}

  ${
    mp3anl2.1 $e |- ps $.
    mp3anl2.2 $e |- ( ( ( ph /\ ps /\ ch ) /\ th ) -> ta ) $.
    $( An inference based on modus ponens. $)
    mp3anl2 $p |- ( ( ( ph /\ ch ) /\ th ) -> ta ) $=
      wph wch wa wth wta wph wps wch wth wta wi mp3anl2.1 wph wps wch w3a wth
      wta mp3anl2.2 ex mp3an2 imp $.
      $( [26-Feb-2005] $) $( [24-Feb-2005] $)
  $}

  ${
    mp3anl3.1 $e |- ch $.
    mp3anl3.2 $e |- ( ( ( ph /\ ps /\ ch ) /\ th ) -> ta ) $.
    $( An inference based on modus ponens. $)
    mp3anl3 $p |- ( ( ( ph /\ ps ) /\ th ) -> ta ) $=
      wph wps wa wth wta wph wps wch wth wta wi mp3anl3.1 wph wps wch w3a wth
      wta mp3anl3.2 ex mp3an3 imp $.
      $( [25-Feb-2005] $) $( [24-Feb-2005] $)
  $}

  ${
    mp3anr1.1 $e |- ps $.
    mp3anr1.2 $e |- ( ( ph /\ ( ps /\ ch /\ th ) ) -> ta ) $.
    $( An inference based on modus ponens. $)
    mp3anr1 $p |- ( ( ph /\ ( ch /\ th ) ) -> ta ) $=
      wch wth wa wph wta wps wch wth wph wta mp3anr1.1 wph wps wch wth w3a wta
      mp3anr1.2 ancoms mp3anl1 ancoms $.
      $( [6-Nov-2006] $) $( [4-Nov-2006] $)
  $}

  ${
    mp3anr2.1 $e |- ch $.
    mp3anr2.2 $e |- ( ( ph /\ ( ps /\ ch /\ th ) ) -> ta ) $.
    $( An inference based on modus ponens. $)
    mp3anr2 $p |- ( ( ph /\ ( ps /\ th ) ) -> ta ) $=
      wps wth wa wph wta wps wch wth wph wta mp3anr2.1 wph wps wch wth w3a wta
      mp3anr2.2 ancoms mp3anl2 ancoms $.
      $( [25-Nov-2006] $) $( [24-Nov-2006] $)
  $}

  ${
    mp3anr3.1 $e |- th $.
    mp3anr3.2 $e |- ( ( ph /\ ( ps /\ ch /\ th ) ) -> ta ) $.
    $( An inference based on modus ponens. $)
    mp3anr3 $p |- ( ( ph /\ ( ps /\ ch ) ) -> ta ) $=
      wps wch wa wph wta wps wch wth wph wta mp3anr3.1 wph wps wch wth w3a wta
      mp3anr3.2 ancoms mp3anl3 ancoms $.
      $( [19-Oct-2007] $) $( [19-Oct-2007] $)
  $}

  ${
    mp3an.1 $e |- ph $.
    mp3an.2 $e |- ps $.
    mp3an.3 $e |- ch $.
    mp3an.4 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mp3an $p |- th $=
      wps wch wth mp3an.2 mp3an.3 wph wps wch wth mp3an.1 mp3an.4 mp3an1 mp2an
      $.
      $( [14-May-1999] $)
  $}

  ${
    mpd3an3.2 $e |- ( ( ph /\ ps ) -> ch ) $.
    mpd3an3.3 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mpd3an3 $p |- ( ( ph /\ ps ) -> th ) $=
      wph wps wa wch wth mpd3an3.2 wph wps wch wth mpd3an3.3 3expa mpdan $.
      $( [12-Nov-2007] $) $( [8-Nov-2007] $)
  $}

  ${
    mpd3an23.1 $e |- ( ph -> ps ) $.
    mpd3an23.2 $e |- ( ph -> ch ) $.
    mpd3an23.3 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( An inference based on modus ponens. $)
    mpd3an23 $p |- ( ph -> th ) $=
      wph wps wch wth wph mpd3an23.3 wph id mpd3an23.1 mpd3an23.2 syl3anc $.
      $( [5-Dec-2006] $) $( [4-Dec-2006] $)
  $}

  ${
    biimp3a.1 $e |- ( ( ph /\ ps ) -> ( ch <-> th ) ) $.
    $( Infer implication from a logical equivalence.  Similar to ~ biimpa . $)
    biimp3a $p |- ( ( ph /\ ps /\ ch ) -> th ) $=
      wph wps wch wth wph wps wa wch wth biimp3a.1 biimpa 3impa $.
      $( [6-Sep-2005] $) $( [4-Sep-2005] $)
  $}

  ${
    3anandis.1 $e |- ( ( ( ph /\ ps ) /\ ( ph /\ ch ) /\ ( ph /\ th ) )
                      -> ta ) $.
    $( Inference that undistributes a triple conjunction in the antecedent. $)
    3anandis $p |- ( ( ph /\ ( ps /\ ch /\ th ) ) -> ta ) $=
      wph wps wa wph wch wa wph wth wa wta wph wps wch wth w3a wa 3anandis.1
      wps wch wth w3a wps wph wps wch wth 3simp1 anim2i wps wch wth w3a wch wph
      wps wch wth 3simp2 anim2i wps wch wth w3a wth wph wps wch wth 3simp3
      anim2i syl3anc $.
      $( [21-Apr-2007] $) $( [18-Apr-2007] $)
  $}

  ${
    3anandirs.1 $e |- ( ( ( ph /\ th ) /\ ( ps /\ th ) /\ ( ch /\ th ) )
                      -> ta ) $.
    $( Inference that undistributes a triple conjunction in the antecedent. $)
    3anandirs $p |- ( ( ( ph /\ ps /\ ch ) /\ th ) -> ta ) $=
      wph wth wa wps wth wa wch wth wa wta wph wps wch w3a wth wa 3anandirs.1
      wph wps wch w3a wph wth wph wps wch 3simp1 anim1i wph wps wch w3a wps wth
      wph wps wch 3simp2 anim1i wph wps wch w3a wch wth wph wps wch 3simp3
      anim1i syl3anc $.
      $( [18-Apr-2007] $) $( [25-Jul-2006] $)
  $}

  ${
    ecase23d.1 $e |- ( ph -> -. ch ) $.
    ecase23d.2 $e |- ( ph -> -. th ) $.
    ecase23d.3 $e |- ( ph -> ( ps \/ ch \/ th ) ) $.
    $( Deduction for elimination by cases. $)
    ecase23d $p |- ( ph -> ps ) $=
      wph wps wch wth wo wph wch wn wth wn wa wch wth wo wn wph wch wn wth wn
      ecase23d.1 ecase23d.2 jca wch wth ioran sylibr wph wps wch wth wo wph wps
      wch wth w3o wps wch wth wo wo ecase23d.3 wps wch wth 3orass sylib ord
      mt3d $.
      $( [15-Jul-2005] $) $( [22-Apr-1994] $)
  $}

  ${
    3ecase.1 $e |- ( -. ph -> th ) $.
    3ecase.2 $e |- ( -. ps -> th ) $.
    3ecase.3 $e |- ( -. ch -> th ) $.
    3ecase.4 $e |- ( ( ph /\ ps /\ ch ) -> th ) $.
    $( Inference for elimination by cases. $)
    3ecase $p |- th $=
      wps wch wth wph wps wch wth wi wi wph wps wch wth 3ecase.4 3exp wph wn
      wch wth wi wps wph wn wth wch 3ecase.1 a1d a1d pm2.61i 3ecase.2 3ecase.3
      pm2.61nii $.
      $( [19-Jul-2005] $) $( [13-Jul-2005] $)
  $}


$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
      Other axiomatizations of classical propositional calculus
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

  $( Carew Meredith's sole axiom for propositional calculus.  This amazing
     formula is thought to be the shortest possible single axiom for
     propositional calculus with inference rule ~ ax-mp , where negation and
     implication are primitive.  Here we prove Meredith's axiom from ~ ax-1 ,
     ~ ax-2 , and ~ ax-3 .  Then from it we derive the Lukasiewicz axioms
     ~ luk-1 , ~ luk-2 , and ~ luk-3 .  Using these we finally re-derive our
     axioms as ~ ax1 , ~ ax2 , and ~ ax3 , thus proving the equivalence of
     all three systems.  C. A. Meredith, "Single Axioms for the Systems
     (C,N), (C,O) and (A,N) of the Two-Valued Propositional Calculus," _The
     Journal of Computing Systems_ vol. 3 (1953), pp. 155-164.  Meredith
     claimed to be close to a proof that this axiom is the shortest possible,
     but the proof was apparently never completed.

     An obscure Irish lecturer, Meredith (1904-1976) became enamored with
     logic somewhat late in life after attending talks by Lukasiewicz and
     produced many remarkable results such as this axiom.  From his obituary:
     "He did logic whenever time and opportunity presented themselves, and he
     did it on whatever materials came to hand:  in a pub, his favored pint
     of porter within reach, he would use the inside of cigarette packs to
     write proofs for logical colleagues." $)
  meredith $p |- ( ( ( ( ( ph -> ps ) -> ( -. ch -> -. th ) ) -> ch ) ->
       ta ) -> ( ( ta -> ph ) -> ( th -> ph ) ) ) $=
    wph wps wi wch wn wth wn wi wi wch wi wta wi wta wn wch wn wch wn wph wn
    wth wn wi wi wn wi wn wi wta wph wi wth wph wi wi wph wps wi wch wn wth wn
    wi wi wch wi wta wi wch wn wch wn wph wn wth wn wi wi wn wi wta wch wn wch
    wn wph wn wth wn wi wi wn wi wph wps wi wch wn wth wn wi wi wch wi wta wch
    wn wch wn wph wn wth wn wi wi wn wi wch wn wph wn wth wn wi wi wch wph wps
    wi wch wn wth wn wi wi wch wch wn wph wn wth wn wi wi ax-3 wph wps wi wch
    wn wth wn wi wi wph wn wch wn wth wn wph wn wph wps wi wch wn wth wn wi wph
    wps pm2.21 imim1i com23 syl5 imim1i con3d wta wn wch wn wch wn wph wn wth
    wn wi wi wn wi wn wi wta wph wi wph wn wth wn wi wth wph wi wta wn wch wn
    wch wn wph wn wth wn wi wi wn wi wn wi wph wn wta wn wi wph wn wth wn wi
    wta wph wi wta wn wch wn wch wn wph wn wth wn wi wi wn wi wn wi wph wn wta
    wn wth wn wph wn wta wn wch wn wch wn wph wn wth wn wi wi wn wi wn wi wta
    wn wth wn wi wph wn wch wn wch wn wph wn wth wn wi wi wn wi wn wth wn wta
    wn wch wn wch wn wph wn wth wn wi wi wn wi wn wph wn wth wn wch wn wch wn
    wph wn wth wn wi wi wph wn wth wn wi wch wn wph wn wth wn wi pm2.27 impi
    com12 imim2d com12 a2d wta wph con3 syl5 wph wth ax-3 syl6 syl $.
    $( [14-Dec-2002] $)

  $( Step 3 of Meredith's proof of Lukasiewicz axioms from his sole axiom.
     (The step numbers refer to Meredith's original paper.) $)
  merlem1 $p |- ( ( ( ch -> ( -. ph -> ps ) ) -> ta ) -> ( ph -> ta ) ) $=
    wta wph wn wi wph wn wps wi wn wph wn wi wi wph wn wps wi wi wch wph wn wps
    wi wi wi wch wph wn wps wi wi wta wi wph wta wi wi wph wn wps wi wta wn wch
    wn wi wn wph wn wps wi wn wn wi wi wta wn wch wn wi wi wta wi wta wph wn wi
    wph wn wps wi wn wph wn wi wi wi wta wph wn wi wph wn wps wi wn wph wn wi
    wi wph wn wps wi wi wch wph wn wps wi wi wi wph wn wps wta wn wch wn wi wph
    wn wps wi wn wta meredith wph wn wps wi wta wn wch wn wi wn wph wn wps wi
    wn wn wi wta wch wta wph wn wi wph wn wps wi wn wph wn wi wi meredith ax-mp
    wta wph wn wph wn wps wi wph wch wph wn wps wi wi meredith ax-mp $.
    $( [14-Dec-2002] $)

  $( Step 4 of Meredith's proof of Lukasiewicz axioms from his sole axiom. $)
  merlem2 $p |- ( ( ( ph -> ph ) -> ch ) -> ( th -> ch ) ) $=
    wch wch wi wph wn wth wn wi wi wph wi wph wph wi wi wph wph wi wch wi wth
    wch wi wi wph wth wn wch wch wi wph merlem1 wch wch wph wth wph wph wi
    meredith ax-mp $.
    $( [14-Dec-2002] $)

  $( Step 7 of Meredith's proof of Lukasiewicz axioms from his sole axiom. $)
  merlem3 $p |- ( ( ( ps -> ch ) -> ph ) -> ( ch -> ph ) ) $=
    wph wph wi wch wn wch wn wi wi wch wi wps wch wi wi wps wch wi wph wi wch
    wph wi wi wch wph wi wps wn wps wn wi wi wps wi wph wph wi wch wn wch wn wi
    wi wi wph wph wi wch wn wch wn wi wi wch wi wps wch wi wi wch wn wch wn wi
    wch wn wch wn wi wi wph wph wi wch wn wch wn wi wi wi wch wph wi wps wn wps
    wn wi wi wps wi wph wph wi wch wn wch wn wi wi wi wch wn wch wn wch wn wi
    wph wph wi merlem2 wch wn wch wn wi wph wph wi wch wn wch wn wi wi wch wph
    wi wps wn wps wn wi wi wps wi merlem2 ax-mp wch wph wps wps wph wph wi wch
    wn wch wn wi wi meredith ax-mp wph wph wch wch wps wch wi meredith ax-mp $.
    $( [14-Dec-2002] $)

  $( Step 8 of Meredith's proof of Lukasiewicz axioms from his sole axiom. $)
  merlem4 $p |- ( ta -> ( ( ta -> ph ) -> ( th -> ph ) ) ) $=
    wph wph wi wth wn wth wn wi wi wth wi wta wi wta wph wi wth wph wi wi wi
    wta wta wph wi wth wph wi wi wi wph wph wth wth wta meredith wta wph wi wth
    wph wi wi wph wph wi wth wn wth wn wi wi wth wi wta merlem3 ax-mp $.
    $( [14-Dec-2002] $)

  $( Step 11 of Meredith's proof of Lukasiewicz axioms from his sole axiom. $)
  merlem5 $p |- ( ( ph -> ps ) -> ( -. -. ph -> ps ) ) $=
    wps wps wi wps wn wps wn wi wi wps wi wps wi wps wps wi wps wps wi wi wi
    wph wps wi wph wn wn wps wi wi wps wps wps wps wps meredith wps wps wi wps
    wn wph wn wn wn wi wi wps wi wph wi wph wps wi wph wn wn wps wi wi wi wps
    wps wi wps wn wps wn wi wi wps wi wps wi wps wps wi wps wps wi wi wi wph
    wps wi wph wn wn wps wi wi wi wps wps wps wph wn wn wph meredith wph wps wi
    wph wn wn wps wi wi wps wps wi wps wn wps wn wi wi wps wi wps wi wps wps wi
    wps wps wi wi wi wn wi wph wn wps wps wi wps wn wps wn wi wi wps wi wps wi
    wps wps wi wps wps wi wi wi wn wi wi wph wi wps wps wi wps wn wph wn wn wn
    wi wi wps wi wph wi wi wps wps wi wps wn wph wn wn wn wi wi wps wi wph wi
    wph wps wi wph wn wn wps wi wi wi wps wps wi wps wn wps wn wi wi wps wi wps
    wi wps wps wi wps wps wi wi wi wph wps wi wph wn wn wps wi wi wi wi wph wps
    wi wph wn wn wps wi wi wps wps wi wps wn wps wn wi wi wps wi wps wi wps wps
    wi wps wps wi wi wi wn wi wph wn wps wps wi wps wn wps wn wi wi wps wi wps
    wi wps wps wi wps wps wi wi wi wn wi wi wph wps wi wph wn wn wps wi wi wps
    wps wi wps wn wps wn wi wi wps wi wps wi wps wps wi wps wps wi wi wi wn wi
    wph wn wps wps wi wps wn wps wn wi wi wps wi wps wi wps wps wi wps wps wi
    wi wi wn wi wi wph wi wps wps wi wps wn wph wn wn wn wi wi wps wi wph wi wi
    wph wn wps wph wps wi wps wps wi wps wn wps wn wi wi wps wi wps wi wps wps
    wi wps wps wi wi wi wn merlem1 wph wps wps wi wps wn wph wn wn wn wi wi wps
    wi wph wps wi wph wn wn wps wi wi wps wps wi wps wn wps wn wi wi wps wi wps
    wi wps wps wi wps wps wi wi wi wn wi wph wn wps wps wi wps wn wps wn wi wi
    wps wi wps wi wps wps wi wps wps wi wi wi wn wi wi merlem4 ax-mp wph wps wi
    wph wn wn wps wi wi wps wps wi wps wn wps wn wi wi wps wi wps wi wps wps wi
    wps wps wi wi wi wn wph wps wps wi wps wn wps wn wi wi wps wi wps wi wps
    wps wi wps wps wi wi wi wps wps wi wps wn wph wn wn wn wi wi wps wi wph wi
    meredith ax-mp ax-mp ax-mp $.
    $( [14-Dec-2002] $)

  $( Step 12 of Meredith's proof of Lukasiewicz axioms from his sole axiom. $)
  merlem6 $p |- ( ch -> ( ( ( ps -> ch ) -> ph ) -> ( th -> ph ) ) ) $=
    wps wch wi wps wch wi wph wi wth wph wi wi wi wch wps wch wi wph wi wth wph
    wi wi wi wph wth wps wch wi merlem4 wps wch wi wph wi wth wph wi wi wps wch
    merlem3 ax-mp $.
    $( [14-Dec-2002] $)

  $( Between steps 14 and 15 of Meredith's proof of Lukasiewicz axioms from his
     sole axiom. $)
  merlem7 $p |- ( ph -> ( ( ( ps -> ch ) -> th ) -> ( ( ( ch -> ta ) ->
                  ( -. th -> -. ps ) ) -> th ) ) ) $=
    wps wch wi wps wch wi wth wi wch wta wi wth wn wps wn wi wi wth wi wi wi
    wph wps wch wi wth wi wch wta wi wth wn wps wn wi wi wth wi wi wi wth wch
    wta wi wth wn wps wn wi wi wps wch wi merlem4 wps wch wi wth wi wch wta wi
    wth wn wps wn wi wi wth wi wi wph wn wi wch wn wph wn wi wi wch wi wps wch
    wi wi wps wch wi wps wch wi wth wi wch wta wi wth wn wps wn wi wi wth wi wi
    wi wph wps wch wi wth wi wch wta wi wth wn wps wn wi wi wth wi wi wi wi wch
    wta wi wth wn wps wn wi wi wth wi wps wch wi wth wi wch wta wi wth wn wps
    wn wi wi wth wi wi wph wn wi wch wn wph wn wi wi wi wps wch wi wth wi wch
    wta wi wth wn wps wn wi wi wth wi wi wph wn wi wch wn wph wn wi wi wch wi
    wps wch wi wi wph wn wps wch wi wth wi wch wta wi wth wn wps wn wi wi wth
    wi wch wn merlem6 wch wta wth wps wps wch wi wth wi wch wta wi wth wn wps
    wn wi wi wth wi wi wph wn wi wch wn wph wn wi wi meredith ax-mp wps wch wi
    wth wi wch wta wi wth wn wps wn wi wi wth wi wi wph wn wch wph wps wch wi
    meredith ax-mp ax-mp $.
    $( [22-Dec-2002] $)

  $( Step 15 of Meredith's proof of Lukasiewicz axioms from his sole axiom. $)
  merlem8 $p |- ( ( ( ps -> ch ) -> th ) -> ( ( ( ch -> ta ) ->
                  ( -. th -> -. ps ) ) -> th ) ) $=
    wph wph wi wph wn wph wn wi wi wph wi wph wi wph wph wi wph wph wi wi wi
    wps wch wi wth wi wch wta wi wth wn wps wn wi wi wth wi wi wph wph wph wph
    wph meredith wph wph wi wph wn wph wn wi wi wph wi wph wi wph wph wi wph
    wph wi wi wi wps wch wth wta merlem7 ax-mp $.
    $( [22-Dec-2002] $)

  ${
    $v et $. $( Greek eta $)
    meredith.we $f wff et $.
    $( Step 18 of Meredith's proof of Lukasiewicz axioms from his sole
       axiom. $)
    merlem9 $p |- ( ( ( ph -> ps ) -> ( ch -> ( th -> ( ps -> ta ) ) ) ) ->
                    ( et -> ( ch -> ( th -> ( ps -> ta ) ) ) ) ) $=
      wch wth wps wta wi wi wi meredith.we wn wi wps wn meredith.we wn wi wi
      wps wi wph wps wi wi wph wps wi wch wth wps wta wi wi wi wi meredith.we
      wch wth wps wta wi wi wi wi wi wps wta wi wch wth wps wta wi wi wi
      meredith.we wn wi wps wn meredith.we wn wi wi wn wth wn wi wn wph wn wi
      wi wch wth wps wta wi wi wi meredith.we wn wi wps wn meredith.we wn wi wi
      wn wth wn wi wi wch wth wps wta wi wi wi meredith.we wn wi wps wn
      meredith.we wn wi wi wi wch wth wps wta wi wi wi meredith.we wn wi wps wn
      meredith.we wn wi wi wps wi wph wps wi wi wth wps wta wi wi wch wth wps
      wta wi wi wi meredith.we wn wi wps wn meredith.we wn wi wi wi wps wta wi
      wch wth wps wta wi wi wi meredith.we wn wi wps wn meredith.we wn wi wi wn
      wth wn wi wn wph wn wi wi wch wth wps wta wi wi wi meredith.we wn wi wps
      wn meredith.we wn wi wi wn wth wn wi wi wch wth wps wta wi wi wi
      meredith.we wn wi wps wn meredith.we wn wi wi wi meredith.we wn wch wth
      wps wta wi wi wps wn merlem6 wth wps wta wi wch wth wps wta wi wi wi
      meredith.we wn wi wps wn meredith.we wn wi wi wch wth wps wta wi wi wi
      meredith.we wn wi wps wn meredith.we wn wi wi wn wth wn wi wn wph wn wi
      merlem8 ax-mp wps wta wch wth wps wta wi wi wi meredith.we wn wi wps wn
      meredith.we wn wi wi wn wth wn wi wph wch wth wps wta wi wi wi
      meredith.we wn wi wps wn meredith.we wn wi wi meredith ax-mp wch wth wps
      wta wi wi wi meredith.we wn wps meredith.we wph wps wi meredith ax-mp $.
      $( [22-Dec-2002] $)
  $}

  $( Step 19 of Meredith's proof of Lukasiewicz axioms from his sole axiom. $)
  merlem10 $p |- ( ( ph -> ( ph -> ps ) ) -> ( th -> ( ph -> ps ) ) ) $=
    wph wph wi wph wn wph wn wi wi wph wi wph wi wph wph wi wph wph wi wi wi
    wph wph wps wi wi wth wph wps wi wi wi wph wph wph wph wph meredith wph wps
    wi wph wi wph wn wth wn wi wi wph wi wph wi wph wph wps wi wi wth wph wps
    wi wi wi wi wph wph wi wph wn wph wn wi wi wph wi wph wi wph wph wi wph wph
    wi wi wi wph wph wps wi wi wth wph wps wi wi wi wi wph wps wi wph wph wth
    wph meredith wph wps wi wph wi wph wn wth wn wi wi wph wi wph wph wph wps
    wi wi wth wps wph wph wi wph wn wph wn wi wi wph wi wph wi wph wph wi wph
    wph wi wi wi merlem9 ax-mp ax-mp $.
    $( [14-Dec-2002] $)

  $( Step 20 of Meredith's proof of Lukasiewicz axioms from his sole axiom. $)
  merlem11 $p |- ( ( ph -> ( ph -> ps ) ) -> ( ph -> ps ) ) $=
    wph wph wi wph wn wph wn wi wi wph wi wph wi wph wph wi wph wph wi wi wi
    wph wph wps wi wi wph wps wi wi wph wph wph wph wph meredith wph wph wps wi
    wi wph wph wps wi wi wph wps wi wi wi wph wph wi wph wn wph wn wi wi wph wi
    wph wi wph wph wi wph wph wi wi wi wph wph wps wi wi wph wps wi wi wi wph
    wps wph wph wps wi wi merlem10 wph wph wps wi wi wph wps wi wph wph wi wph
    wn wph wn wi wi wph wi wph wi wph wph wi wph wph wi wi wi merlem10 ax-mp
    ax-mp $.
    $( [14-Dec-2002] $)

  $( Step 28 of Meredith's proof of Lukasiewicz axioms from his sole axiom. $)
  merlem12 $p |- ( ( ( th -> ( -. -. ch -> ch ) ) -> ph ) -> ph ) $=
    wth wch wn wn wch wi wi wph wi wth wch wn wn wch wi wi wph wi wph wi wi wth
    wch wn wn wch wi wi wph wi wph wi wth wch wn wn wch wi wi wth wch wn wn wch
    wi wi wph wi wth wch wn wn wch wi wi wph wi wph wi wi wch wch wi wch wn wn
    wch wi wi wth wch wn wn wch wi wi wch wch merlem5 wch wch wn wn wch wi wth
    merlem2 ax-mp wph wth wch wn wn wch wi wi wph wi wth wch wn wn wch wi wi
    merlem4 ax-mp wth wch wn wn wch wi wi wph wi wph merlem11 ax-mp $.
    $( [14-Dec-2002] $)

  $( Step 35 of Meredith's proof of Lukasiewicz axioms from his sole axiom. $)
  merlem13 $p |- ( ( ph -> ps ) ->
              ( ( ( th -> ( -. -. ch -> ch ) ) -> -. -. ph ) -> ps ) ) $=
    wps wps wi wph wn wth wch wn wn wch wi wi wph wn wn wi wn wi wi wph wi wph
    wi wph wps wi wth wch wn wn wch wi wi wph wn wn wi wps wi wi wps wps wi wph
    wn wth wch wn wn wch wi wi wph wn wn wi wn wi wi wph wi wps wps wi wph wn
    wth wch wn wn wch wi wi wph wn wn wi wn wi wi wph wi wph wi wi wps wps wi
    wph wn wth wch wn wn wch wi wi wph wn wn wi wn wi wi wph wi wph wi wph wn
    wth wch wn wn wch wi wi wph wn wn wi wn wi wps wps wi wph wn wth wch wn wn
    wch wi wi wph wn wn wi wn wi wi wph wi wps wps wi wph wn wth wch wn wn wch
    wi wi wph wn wn wi wn wi wi wph wi wph wi wi wth wch wn wn wch wi wi wth
    wch wn wn wch wi wi wph wn wn wi wn wi wth wch wn wn wch wi wi wph wn wn wi
    wn wi wph wn wth wch wn wn wch wi wi wph wn wn wi wn wi wth wch wn wn wch
    wi wi wph wn wn wi wn wch wth merlem12 wth wch wn wn wch wi wi wph wn wn wi
    wn wps wi wth wch wn wn wch wi wi wph wn wn wi wn wn wph wn wn wi wi wth
    wch wn wn wch wi wi wph wn wn wi wn wi wth wch wn wn wch wi wi wth wch wn
    wn wch wi wi wph wn wn wi wn wi wi wth wch wn wn wch wi wi wth wch wn wn
    wch wi wi wph wn wn wi wn wi wth wch wn wn wch wi wi wph wn wn wi wn wi wph
    wn wth wch wn wn wch wi wi wph wn wn wi wn wi wi wth wch wn wn wch wi wi
    wph wn wn wi wn wn wph wn wn wi wth wch wn wn wch wi wi wph wn wn wi wn wps
    wi wth wch wn wn wch wi wi wph wn wn wi wn wn wph wn wn wi wi wth wch wn wn
    wch wi wi wph wn wn wi wn wi wth wch wn wn wch wi wi wth wch wn wn wch wi
    wi wph wn wn wi wn wi wi wth wch wn wn wch wi wi wph wn wn wi wph wn wn wi
    wth wch wn wn wch wi wi wph wn wn wi wn wn wph wn wn wi wph wn wn wch wth
    merlem12 wth wch wn wn wch wi wi wph wn wn wi wph wn wn merlem5 ax-mp wth
    wch wn wn wch wi wi wph wn wn wi wn wth wch wn wn wch wi wi wph wn wn wi wn
    wps wi wth wch wn wn wch wi wi wph wn wn wi wn wn wph wn wn wi wth wch wn
    wn wch wi wi merlem6 ax-mp wth wch wn wn wch wi wi wph wn wn wi wn wps wth
    wch wn wn wch wi wi wph wn wn wi wn wph wn wth wch wn wn wch wi wi wth wch
    wn wn wch wi wi wph wn wn wi wn wi meredith ax-mp ax-mp wph wps wps wi wph
    wn wth wch wn wn wch wi wi wph wn wn wi wn wi wps wps wi wph wn wth wch wn
    wn wch wi wi wph wn wn wi wn wi wi wph wi merlem6 ax-mp wps wps wi wph wn
    wth wch wn wn wch wi wi wph wn wn wi wn wi wi wph wi wph merlem11 ax-mp wps
    wps wph wth wch wn wn wch wi wi wph wn wn wi wph meredith ax-mp $.
    $( [14-Dec-2002] $)

  $( 1 of 3 axioms for propositional calculus due to Lukasiewicz, derived from
     Meredith's sole axiom. $)
  luk-1 $p |- ( ( ph -> ps ) -> ( ( ps -> ch ) -> ( ph -> ch ) ) ) $=
    wch wch wi wph wn wn wn wph wn wi wi wph wn wn wi wps wi wps wch wi wph wch
    wi wi wi wph wps wi wps wch wi wph wch wi wi wi wch wch wph wn wn wph wps
    meredith wps wch wi wph wch wi wi wph wi wph wps wi wn wn wn wph wps wi wn
    wi wi wph wps wi wn wn wi wch wch wi wph wn wn wn wph wn wi wi wph wn wn wi
    wps wi wi wch wch wi wph wn wn wn wph wn wi wi wph wn wn wi wps wi wps wch
    wi wph wch wi wi wi wph wps wi wps wch wi wph wch wi wi wi wi wph wps wi
    wch wch wi wph wn wn wn wph wn wi wi wph wn wn wi wps wi wi wps wch wi wph
    wch wi wi wph wi wph wps wi wn wn wn wph wps wi wn wi wi wph wps wi wn wn
    wi wch wch wi wph wn wn wn wph wn wi wi wph wn wn wi wps wi wi wph wps wph
    wn wch wch wi merlem13 wph wps wi wch wch wi wph wn wn wn wph wn wi wi wph
    wn wn wi wps wi wph wps wi wn wps wch wi wph wch wi wi wph wi merlem13
    ax-mp wps wch wi wph wch wi wi wph wph wps wi wn wn wph wps wi wch wch wi
    wph wn wn wn wph wn wi wi wph wn wn wi wps wi meredith ax-mp ax-mp $.
    $( [14-Dec-2002] $)

  $( 2 of 3 axioms for propositional calculus due to Lukasiewicz, derived from
     Meredith's sole axiom. $)
  luk-2 $p |- ( ( -. ph -> ph ) -> ph ) $=
    wph wn wph wi wph wn wph wi wph wi wi wph wn wph wi wph wi wph wph wn wph
    wi wn wi wph wn wn wph wn wph wi wn wi wi wph wn wi wph wn wi wph wn wph wi
    wph wn wph wi wph wi wi wph wph wn wph wi wn wi wph wn wn wph wn wph wi wn
    wi wi wph wn wi wph wph wn wph wi wn wi wph wn wn wph wn wph wi wn wi wi
    wph wn wi wph wn wi wi wph wph wn wph wi wn wi wph wn wn wph wn wph wi wn
    wi wi wph wn wi wph wn wi wph wph wn wph wi wn wi wph wn wn wph wn wph wi
    wn wi wi wph wph wn wph wi wn wi wph wn wn wph wn wph wi wn wi wi wph wn wi
    wph wph wn wph wi wn wi wph wn wn wph wn wph wi wn wi wi wph wn wi wph wn
    wi wi wph wph wn wph wi wn merlem5 wph wn wph wph wn wph wi wn wi wph wn wn
    wph wn wph wi wn wi wi wph wn wi wph wph wn wph wi wn wi wph wn wn wph wn
    wph wi wn wi wi merlem4 ax-mp wph wph wn wph wi wn wi wph wn wn wph wn wph
    wi wn wi wi wph wn wi wph wn merlem11 ax-mp wph wph wn wph wi wn wph wn wph
    wn wph wi wph wn meredith ax-mp wph wn wph wi wph merlem11 ax-mp $.
    $( [14-Dec-2002] $)

  $( 3 of 3 axioms for propositional calculus due to Lukasiewicz, derived from
     Meredith's sole axiom. $)
  luk-3 $p |- ( ph -> ( -. ph -> ps ) ) $=
    wph wn wph wn wps wi wi wph wn wps wi wi wph wph wn wps wi wi wph wn wps
    merlem11 wph wps wph wn wph wn wps wi merlem1 ax-mp $.
    $( [14-Dec-2002] $)

  ${
    luklem1.1 $e |- ( ph -> ps ) $.
    luklem1.2 $e |- ( ps -> ch ) $.
    $( Used to rederive standard propositional axioms from Lukasiewicz'. $)
    luklem1 $p |- ( ph -> ch ) $=
      wps wch wi wph wch wi luklem1.2 wph wps wi wps wch wi wph wch wi wi
      luklem1.1 wph wps wch luk-1 ax-mp ax-mp $.
      $( [23-Dec-2002] $)
  $}

  $( Used to rederive standard propositional axioms from Lukasiewicz'. $)
  luklem2 $p |- ( ( ph -> -. ps ) ->
                ( ( ( ph -> ch ) -> th ) -> ( ps -> th ) ) ) $=
    wph wps wn wi wps wph wch wi wi wph wch wi wth wi wps wth wi wi wph wps wn
    wi wps wn wch wi wph wch wi wi wps wph wch wi wi wph wps wn wch luk-1 wps
    wps wn wch wi wi wps wn wch wi wph wch wi wi wps wph wch wi wi wi wps wch
    luk-3 wps wps wn wch wi wph wch wi luk-1 ax-mp luklem1 wps wph wch wi wth
    luk-1 luklem1 $.
    $( [22-Dec-2002] $)

  $( Used to rederive standard propositional axioms from Lukasiewicz'. $)
  luklem3 $p |- ( ph -> ( ( ( -. ph -> ps ) -> ch ) -> ( th -> ch ) ) ) $=
    wph wph wn wth wn wi wph wn wps wi wch wi wth wch wi wi wph wth wn luk-3
    wph wn wth wps wch luklem2 luklem1 $.
    $( [22-Dec-2002] $)

  $( Used to rederive standard propositional axioms from Lukasiewicz'. $)
  luklem4 $p |- ( ( ( ( -. ph -> ph ) -> ph ) -> ps ) -> ps ) $=
    wph wn wph wi wph wi wps wi wps wn wps wi wps wps wn wph wn wph wi wph wi
    wi wph wn wph wi wph wi wps wi wps wn wps wi wi wph wn wph wi wph wi wn wph
    wn wph wi wph wi wi wph wn wph wi wph wi wi wps wn wph wn wph wi wph wi wi
    wph wn wph wi wph wi luk-2 wph wn wph wi wph wi wph wn wph wi wph wi wn wph
    wn wph wi wph wi wi wph wn wph wi wph wi wi wps wn wph wn wph wi wph wi wi
    wi wph luk-2 wph wn wph wi wph wi wph wn wph wi wph wi wph wn wph wi wph wi
    wps wn luklem3 ax-mp ax-mp wps wn wph wn wph wi wph wi wps luk-1 ax-mp wps
    luk-2 luklem1 $.
    $( [22-Dec-2002] $)

  $( Used to rederive standard propositional axioms from Lukasiewicz'. $)
  luklem5 $p |- ( ph -> ( ps -> ph ) ) $=
    wph wph wn wph wi wph wi wps wph wi wi wps wph wi wph wph wph wps luklem3
    wph wps wph wi luklem4 luklem1 $.
    $( [22-Dec-2002] $)

  $( Used to rederive standard propositional axioms from Lukasiewicz'. $)
  luklem6 $p |- ( ( ph -> ( ph -> ps ) ) -> ( ph -> ps ) ) $=
    wph wph wps wi wi wph wps wi wps wi wph wps wi wi wph wps wi wph wph wps wi
    wps luk-1 wph wps wi wn wph wps wi wi wph wps wi wi wph wps wi wps wi wph
    wps wi wi wph wps wi wi wi wph wps wi wps wi wph wps wi wi wph wps wi wi
    wph wps wi wps wi wph wps wi wi wph wps wi wn wph wps wi wi wi wph wps wi
    wn wph wps wi wi wph wps wi wi wph wps wi wps wi wph wps wi wi wph wps wi
    wi wi wph wps wi wn wph wps wi wps wi wi wph wps wi wps wi wph wps wi wi
    wph wps wi wn wph wps wi wi wi wph wps wi wn wps wn wph wps wi wn wi wph
    wps wi wps wi wph wps wi wn wps wn luklem5 wps wn wph wps wi wn wi wps wn
    wps wi wps wi wph wps wi wps wi wi wph wps wi wps wi wps wn wph wps wi wps
    wps luklem2 wps wph wps wi wps wi luklem4 luklem1 luklem1 wph wps wi wn wph
    wps wi wps wi wph wps wi luk-1 ax-mp wph wps wi wps wi wph wps wi wi wph
    wps wi wn wph wps wi wi wph wps wi luk-1 ax-mp wph wps wi wph wps wi wps wi
    wph wps wi wi wph wps wi wi luklem4 ax-mp luklem1 $.
    $( [22-Dec-2002] $)

  $( Used to rederive standard propositional axioms from Lukasiewicz'. $)
  luklem7 $p |- ( ( ph -> ( ps -> ch ) ) -> ( ps -> ( ph -> ch ) ) ) $=
    wph wps wch wi wi wps wch wi wch wi wph wch wi wi wps wph wch wi wi wph wps
    wch wi wch luk-1 wps wps wch wi wch wi wi wps wch wi wch wi wph wch wi wi
    wps wph wch wi wi wi wps wps wch wi wps wch wi wch wi wi wps wch wi wch wi
    wps wps wch wi wps wi wps wch wi wps wch wi wch wi wi wps wps wch wi
    luklem5 wps wch wi wps wch luk-1 luklem1 wps wch wi wch luklem6 luklem1 wps
    wps wch wi wch wi wph wch wi luk-1 ax-mp luklem1 $.
    $( [22-Dec-2002] $)

  $( Used to rederive standard propositional axioms from Lukasiewicz'. $)
  luklem8 $p |- ( ( ph -> ps ) -> ( ( ch -> ph ) -> ( ch -> ps ) ) ) $=
    wch wph wi wph wps wi wch wps wi wi wi wph wps wi wch wph wi wch wps wi wi
    wi wch wph wps luk-1 wch wph wi wph wps wi wch wps wi luklem7 ax-mp $.
    $( [22-Dec-2002] $)

  $( Standard propositional axiom derived from Lukasiewicz axioms. $)
  ax1 $p |- ( ph -> ( ps -> ph ) ) $=
    wph wps luklem5 $.
    $( [22-Dec-2002] $)

  $( Standard propositional axiom derived from Lukasiewicz axioms. $)
  ax2 $p |- ( ( ph -> ( ps -> ch ) ) -> ( ( ph -> ps ) -> ( ph -> ch ) ) ) $=
    wph wps wch wi wi wps wph wch wi wi wph wps wi wph wch wi wi wph wps wch
    luklem7 wps wph wch wi wi wph wps wi wph wph wch wi wi wi wph wps wi wph
    wch wi wi wps wph wch wi wph luklem8 wph wph wch wi wi wph wch wi wi wph
    wps wi wph wph wch wi wi wi wph wps wi wph wch wi wi wi wph wch luklem6 wph
    wph wch wi wi wph wch wi wph wps wi luklem8 ax-mp luklem1 luklem1 $.
    $( [22-Dec-2002] $)

  $( Standard propositional axiom derived from Lukasiewicz axioms. $)
  ax3 $p |- ( ( -. ph -> -. ps ) -> ( ps -> ph ) ) $=
    wph wn wps wn wi wph wn wph wi wph wi wps wph wi wi wps wph wi wph wn wps
    wph wph luklem2 wph wps wph wi luklem4 luklem1 $.
    $( [22-Dec-2002] $)

  $( Axiom of Nicod from _Introduction to Mathematical Philosophy_ B. Russell,
     p. 152.  The axiom is recovered from this raw form by substituting
     ` ( ph | ps ) ` for ` -. ( ph /\ ps ) ` , where ` | ` is the Sheffer
     stroke (NAND) connective, so that the Sheffer stroke becomes the sole
     connective.  See ~ nicodmpraw for the inference rule.  (Based on a proof
     by Jeff Hoffman, 19-Nov-2007.) $)
  nicodraw $p |- -. ( -. ( ph /\ -. ( ch /\ ps ) ) /\ -. ( -. ( ta /\
      -. ( ta /\ ta ) ) /\ -. ( -. ( th /\ ch ) /\ -. ( -. ( ph /\ th ) /\
         -. ( ph /\ th ) ) ) ) ) $=
    wph wch wps wa wn wa wn wta wta wta wa wn wa wn wth wch wa wn wph wth wa wn
    wph wth wa wn wa wn wa wn wa wi wph wch wps wa wn wa wn wta wta wta wa wn
    wa wn wth wch wa wn wph wth wa wn wph wth wa wn wa wn wa wn wa wn wa wn wph
    wch wps wa wn wa wn wth wch wa wn wph wth wa wn wph wth wa wn wa wn wa wn
    wta wta wta wa wn wa wn wph wch wps wa wn wa wn wph wch wps wa wi wph wch
    wi wth wch wa wn wph wth wa wn wph wth wa wn wa wn wa wn wph wch wps wa wi
    wph wch wps wa wn wa wn wph wch wps wa iman biimpr wch wps wa wch wph wch
    wps pm3.26 imim2i wph wch wi wth wch wa wn wph wth wa wn wi wth wch wa wn
    wph wth wa wn wph wth wa wn wa wn wa wn wph wch wi wth wch wn wi wph wth wa
    wn wth wch wa wn wph wch wi wth wch wn wi wth wph wn wi wph wth wa wn wph
    wch wi wch wn wph wn wth wph wch con3 imim2d wth wph wn wi wph wth wn wi
    wph wth wa wn wth wph bi2.03 wph wth imnan bitr2 syl6ibr wth wch imnan
    syl5ibr wth wch wa wn wph wth wa wn wph wth wa wn wa wn wa wn wth wch wa wn
    wph wth wa wn wph wth wa wn wa wi wth wch wa wn wph wth wa wn wi wth wch wa
    wn wph wth wa wn wph wth wa wn wa iman wph wth wa wn wph wth wa wn wa wph
    wth wa wn wth wch wa wn wph wth wa wn anidm imbi2i bitr3 sylibr 3syl wta
    wta wta wa wi wta wta wta wa wn wa wn wta wta wta wa wta pm4.24 biimp wta
    wta wta wa iman mpbi jctil wph wch wps wa wn wa wn wta wta wta wa wn wa wn
    wth wch wa wn wph wth wa wn wph wth wa wn wa wn wa wn wa iman mpbi $.
    $( [20-Nov-2007] $) $( [19-Nov-2007] $)

  $(${
    nicmin $e |- ph $.
    nicmaj $e |- -. ( ph /\ -. ( ch /\ ps ) ) $.
    nicodmpraw $p |- ps $=
      wph wps nicmin wph wch wps wph wch wps wa wi wph wch wps wa wn wa wn
      nicmaj wph wch wps wa iman mpbir pm3.27d ax-mp $.
  $}
$)
