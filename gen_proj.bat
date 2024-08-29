@REM make vs project
xmake f -a x86 --skip_codegen=n --make_artifacts=y
xmake project -k vsxmake -m "debug,release" -y -v
