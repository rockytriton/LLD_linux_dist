echo "Dist Root: ${DIST_ROOT:?}"
echo "LFS: ${LFS:?}"

if ! test $(whoami) == "distbuild" ; then
    echo "Must run as distbuild!"
    exit -1
fi

echo "Creating build environment..."
