{
  description = "interception mmk";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
  } @ inputs: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    packages.${system}.default = pkgs.stdenv.mkDerivation {
      name = "interception-mmk";
      src = ./.;
      nativeBuildInputs = [pkgs.cmake];

      installPhase = ''
        mkdir -p $out/bin/
        cp interception-* $out/bin/
      '';
    };
  };
}
