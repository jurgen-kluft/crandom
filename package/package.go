package crandom

import (
	cbase "github.com/jurgen-kluft/cbase/package"
	"github.com/jurgen-kluft/ccode/denv"
	cunittest "github.com/jurgen-kluft/cunittest/package"
)

// GetPackage returns the package object of 'crandom'
func GetPackage() *denv.Package {
	// Dependencies
	cunittestpkg := cunittest.GetPackage()
	cbasepkg := cbase.GetPackage()

	// The main (crandom) package
	mainpkg := denv.NewPackage("crandom")
	mainpkg.AddPackage(cunittestpkg)
	mainpkg.AddPackage(cbasepkg)

	// 'crandom' library
	mainlib := denv.SetupDefaultCppLibProject("crandom", "github.com\\jurgen-kluft\\crandom")
	mainlib.Dependencies = append(mainlib.Dependencies, cbasepkg.GetMainLib())

	// 'crandom' unittest project
	maintest := denv.SetupDefaultCppTestProject("crandom_test", "github.com\\jurgen-kluft\\crandom")
	maintest.Dependencies = append(maintest.Dependencies, cunittestpkg.GetMainLib())
	maintest.Dependencies = append(maintest.Dependencies, cbasepkg.GetMainLib())
	maintest.Dependencies = append(maintest.Dependencies, mainlib)

	mainpkg.AddMainLib(mainlib)
	mainpkg.AddUnittest(maintest)
	return mainpkg
}
