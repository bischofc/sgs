#!/bin/bash

tools/cinclude2dot.pl --exclude "\.cpp$" --include lib/builder,lib/helper,lib/simulation,contrib/tinyxml --quotetypes quote > dots.dot
dot -Tps dots.dot > dots.ps
gv dots.ps
rm dots.dot
