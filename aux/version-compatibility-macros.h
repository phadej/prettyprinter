#ifndef VERSION_COMPATIBILITY_MACROS
#define VERSION_COMPATIBILITY_MACROS

#ifndef MIN_VERSION_base
#error "MIN_VERSION_base macro not defined!"
#endif

-- These macros allow writing CPP compatibility hacks in a way that makes their
-- purpose much clearer than just demanding a specific version of a library.

#define APPLICATIVE_MONAD               MIN_VERSION_base(4,8,0)
#define FOLDABLE_TRAVERSABLE_IN_PRELUDE MIN_VERSION_base(4,8,0)
#define FUNCTOR_IDENTITY_IN_BASE        MIN_VERSION_base(4,8,0)
#define MONOID_IN_PRELUDE               MIN_VERSION_base(4,8,0)
#define NATURAL_IN_BASE                 MIN_VERSION_base(4,8,0)

#define SEMIGROUP_IN_BASE               MIN_VERSION_base(4,9,0)

#define NO_FAIL_IN_MONAD_MONAD_FAIL     MIN_VERSION_base(4,13,0)

#define HAS_GENERICS                    __GLASGOW_HASKELL__ >= 702

#endif
