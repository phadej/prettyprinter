<!-- This file was auto-generated by the 'scripts/generate_readme' program. -->



A modern Wadler/Leijen Prettyprinter
====================================

[![](https://img.shields.io/travis/quchen/prettyprinter/master.svg?style=flat-square&label=Master%20build)](https://travis-ci.org/quchen/prettyprinter)
[![](https://img.shields.io/hackage/v/prettyprinter.svg?style=flat-square&label=Hackage&colorB=0a7bbb)](https://hackage.haskell.org/package/prettyprinter)
[![](https://www.stackage.org/package/prettyprinter/badge/lts?style=flat-square&colorB=0a7bbb)](https://www.stackage.org/package/prettyprinter)
[![](https://www.stackage.org/package/prettyprinter/badge/nightly?style=flat-square&label=stackage%20nightly&colorB=0a7bbb)](https://www.stackage.org/package/prettyprinter)



tl;dr
-----

A prettyprinter/text rendering engine. Easy to use, well-documented, ANSI
terminal backend exists, HTML backend is trivial to implement, no name clashes,
`Text`-based, extensible.

```haskell
let prettyType = align . sep . zipWith (<+>) ("::" : repeat "->")
    prettySig name ty = pretty name <+> prettyType ty
in  prettySig "example" ["Int", "Bool", "Char", "IO ()"]
```

```haskell
-- Output for wide enough formats:
example :: Int -> Bool -> Char -> IO ()

-- Output for narrow formats:
example :: Int
        -> Bool
        -> Char
        -> IO ()
```




Longer; want to read
--------------------

This package defines a prettyprinter to format text in a flexible and convenient
way. The idea is to combine a document out of many small components, then using
a layouter to convert it to an easily renderable simple document, which can then
be rendered to a variety of formats, for example plain `Text`, or Markdown.
*What you are reading right now was generated by this library (see
`GenerateReadme.hs`).*



Why another prettyprinter?
--------------------------

Haskell, more specifically Hackage, has a zoo of Wadler/Leijen based
prettyprinters already. Each of them addresses a different concern with the
classic `wl-pprint` package. This package solves *all* these issues, and then
some.



### `Text` instead of `String`

`String` has exactly one use, and that’s showing Hello World in tutorials. For
all other uses, `Text` is what people should be using. The prettyprinter uses no
`String` definitions anywhere; using a `String` means an immediate conversion to
the internal `Text`-based format.



### Extensive documentation

The library is stuffed with runnable examples, showing use cases for the vast
majority of exported values. Many things reference related definitions,
*everything* comes with at least a sentence explaining its purpose.



### No name clashes

Many prettyprinters use the legacy API of the first Wadler/Leijen prettyprinter,
which used e.g. `(<$>)` to separate lines, which clashes with the ubiquitous
synonym for `fmap` that’s been in Base for ages. These definitions were either
removed or renamed, so there are no name clashes with standard libraries
anymore.



### Annotation support

Text is not all letters and newlines. Often, we want to add more information,
the simplest kind being some form of styling. An ANSI terminal supports
coloring, a web browser a plethora of different formattings.

More complex uses of annotations include e.g. adding type annotations for
mouse-over hovers when printing a syntax tree, adding URLs to documentation, or
adding source locations to show where a certain piece of output comes from.
[Idris](https://github.com/idris-lang/Idris-dev) is a project that makes
extensive use of such a feature.

Special care has been applied to make annotations unobtrusive, so that if you
don’t need or care about them there is no overhead, neither in terms of
usability nor performance.



### Extensible backends

A document can be rendered in many different ways, for many different clients.
There is plain text, there is the ANSI terminal, there is the browser. Each of
these speak different languages, and the backend is responsible for the
translation to those languages. Backends should be readily available, or easy to
implement if a custom solution is desired.

As a result, each backend requires only minimal dependencies; if you don’t want
to print to an ANSI terminal for example, there is no need to have a dependency
on a terminal library.



### Performance

Rendering large documents should be done efficiently, and the library should
make it easy to optimize common use cases for the programmer.



### Open implementation

The type of documents is abstract in most of the other Wadler/Leijen
prettyprinters, making it hard to impossible to write adaptors from one library
to another. The type should be exposed for such purposes so it is possible to
write adaptors from library to library, or each of them is doomed to live on its
own small island of incompatibility. For this reason, the `Doc` type is fully
exposed in a semi-internal module for this specific use case.



The prettyprinter family
------------------------

The `prettyprinter` family of packages consists of:

  - `prettyprinter` is the core package. It defines the language to generate
    nicely laid out documents, which can then be given to renderers to display
    them in various ways, e.g. HTML, or plain text.
  - `prettyprinter-ansi-terminal` provides a renderer suitable for ANSI terminal
    output including colors (at the cost of a dependency more).
  - `prettyprinter-compat-wl-pprint` provides a drop-in compatibility layer for
    previous users of the `wl-pprint` package. Use it for easy adaption of the
    new `prettyprinter`, but don't develop anything new with it.
  - `prettyprinter-compat-ansi-wl-pprint` is the same, but for previous users of
    `ansi-wl-pprint`.
  - `prettyprinter-compat-annotated-wl-pprint` is the same, but for previous
    users of `annotated-wl-pprint`.
  - `prettyprinter-convert-ansi-wl-pprint` is a *converter*, not a drop-in
    replacement, for documents generated by `ansi-wl-pprint`. Useful for
    interfacing with other libraries that use the other format, like Trifecta
    and Optparse-Applicative.



Differences to the old Wadler/Leijen prettyprinters
---------------------------------------------------

The library originally started as a fork of `ansi-wl-pprint` until every line
had been touched. The result is still in the same spirit as its predecessors,
but modernized to match the current ecosystem and needs.

The most significant changes are:

  1. `(<$>)` is removed as an operator, since it clashes with the common alias
     for `fmap`.
  2. All but the essential `<>` and `<+>` operators were removed or replaced by
     ordinary names.
  3. Everything extensively documented, with references to other functions and
     runnable code examples.
  4. Use of `Text` instead of `String`.
  5. A `fuse` function to optimize often-used documents before rendering for
     efficiency.
  6. SimpleDoc was renamed `SimpleDocStream`, to contrast the new
     `SimpleDocTree`.
  7. In the ANSI backend, instead of providing an own colorization function for
     each color/intensity/layer combination, they have been combined in `color`,
     `colorDull`, `bgColor`, and `bgColorDull` functions, which can be found in
     the ANSI terminal specific `prettyprinter-ansi-terminal` package.



Historical notes
----------------

This module is based on previous work by Daan Leijen and Max Bolingbroke, who
implemented and significantly extended the prettyprinter given by a [paper by
Phil Wadler in his 1997 paper »A Prettier
Printer«](https://homepages.inf.ed.ac.uk/wadler/papers/prettier/prettier.pdf),
by adding lots of convenience functions, styling, and new functionality. Their
package, ansi-wl-pprint is widely used in the Haskell ecosystem, and is at the
time of writing maintained by Edward Kmett.
