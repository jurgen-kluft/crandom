package crandom

import (
	cbase "github.com/jurgen-kluft/cbase/package"
	denv "github.com/jurgen-kluft/ccode/denv"
	ccore "github.com/jurgen-kluft/ccore/package"
	cunittest "github.com/jurgen-kluft/cunittest/package"
)

// GetPackage returns the package object of 'crandom'
func GetPackage() *denv.Package {
	// Dependencies
	cunittestpkg := cunittest.GetPackage()
	cbasepkg := cbase.GetPackage()
	ccorepkg := ccore.GetPackage()

	// The main (crandom) package
	mainpkg := denv.NewPackage("crandom")
	mainpkg.AddPackage(cunittestpkg)
	mainpkg.AddPackage(cbasepkg)
	mainpkg.AddPackage(ccorepkg)

	// 'crandom' library
	mainlib := denv.SetupCppLibProject("crandom", "github.com\\jurgen-kluft\\crandom")
	mainlib.AddDependencies(cbasepkg.GetMainLib()...)
	mainlib.AddDependencies(ccorepkg.GetMainLib()...)

	// 'crandom' unittest project
	maintest := denv.SetupDefaultCppTestProject("crandom_test", "github.com\\jurgen-kluft\\crandom")
	maintest.AddDependencies(cunittestpkg.GetMainLib()...)
	maintest.AddDependencies(cbasepkg.GetMainLib()...)
	maintest.AddDependencies(ccorepkg.GetMainLib()...)
	maintest.Dependencies = append(maintest.Dependencies, mainlib)

	mainpkg.AddMainLib(mainlib)
	mainpkg.AddUnittest(maintest)
	return mainpkg
}
