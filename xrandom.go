package main

import (
	"github.com/jurgen-kluft/xcode"
	"github.com/jurgen-kluft/xrandom/package"
)

func main() {
	xcode.Init()
	xcode.Generate(xrandom.GetPackage())
}
