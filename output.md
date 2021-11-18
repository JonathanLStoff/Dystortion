![](.//media/image1.jpg){width="5.850734908136483in"
height="1.7040977690288714in"}

**Welcome to my github repository for Dystortion Audio Plugin.**

**[[Donate]{.underline}](https://www.paypal.com/donate?hosted_button_id=9ELH753DDE98Y)
\| [[Website]{.underline}](https://linktr.ee/stoffaudio) \|
[[Email]{.underline}](mailto:stoffaudio@gmail.com)**

This is a DAW plugin that took me a long time to craft but the time and
effort was worth it. In this description I will be going over the long
journey it took for me to go from an Audio Engineer, with no
understanding of C++ or compiling, to creating this plugin.

**[Installation Instructions]{.underline}**

**[Mac (OSX):]{.underline}**

-   Download the Package from the releases on the right.

-   Open the file and you will get a warning like this:

![](.//media/image5.png){width="1.7552088801399826in"
height="2.0826727909011375in"}

-   Open "System Preferences" and select "Open anyway"

> ![](.//media/image9.png){width="4.880208880139983in"
> height="4.291586832895888in"}

-   Then you just install normally:

-   It will install AAX in "Macintosh HD/Library/Application
    > Support/Avid/Audio/Plug-Ins",![](.//media/image7.png){width="3.3110837707786525in"
    > height="2.348824365704287in"}![](.//media/image8.png){width="3.2902023184601923in"
    > height="2.346379046369204in"}

> install VST3 in "Macintosh HD/Users/\[YOUR
> USER\]/Library/Audio/Plug-Ins/VST3",
>
> And install AU in "Macintosh HD/Users/\[YOUR
> USER\]/Library/Audio/Plug-Ins/Components"

**[Windows:]{.underline}**

-   Download the Package from the releases on the right.

-   Open the file and you will get a warning like this:

> ![](.//media/image3.png){width="2.994792213473316in"
> height="2.7438615485564304in"}

-   Click "[More info]{.underline}", then click "Run anyway":

![](.//media/image6.png){width="2.995718503937008in"
height="2.7864588801399823in"}

-   It will install AAX in "C:\\Program Files\\Common
    > Files\\Avid\\Audio\\Plug-Ins"

> And install VST3 in "C:\\Program Files\\Common Files\\VST3"

I need to preface this with sharing that I do have ADHD, making my
learning technique very different to the average joe. I can't learn
things by myself unless I am doing. For example: I would never just
start reading a book on C++ and doing sample projects to learn how to
use it. I want to start making the program I want and look up elements
to add along the
way.![](.//media/image10.png){width="2.7239588801399823in"
height="4.099978127734033in"}

I started this journey by asking some of my old Music Tech teachers from
University what I should start off doing. I had some understanding of
the physics of sound waves and DSP technology, but only a minor in
Computer engineering. My teacher told me to start with MAX 8. This was a
good idea except that we had exhausted this program while in class. It
has great tools for understanding how you can multiply signals, create
FM signals, and other kinds of modifications you can make to sound
waves. I would highly recommend it to visual learners and if you just
want to see about this sort of thing first.

A quick google search told me I should check out JUCE framework. At this
point the only coding experience I had was with Visual Basic,
Applescript, HTML, & CSS. None of which were close to what I would have
to deal with in this C++ adventure. I also had no idea how github worked
but I was able to download the JUCE release. Here is where my first snag
was, I had to code on a Mac book with an ARM chip (M1). This wouldn't
have been as much as an issue but I wanted to use VS Code so I could
access Github Copilot. After a bit of google searching I found a tool
called "FRUT" a CMake-Maker for JUCE. This was a great tool, I was able
to follow the instructions and found that I worked pretty well. Just
added the CMAKE tools extension to VS code, downloaded cmake, researched
what the heck a command palette was, used the shortcut (CMD+SHFT+P),
searched "settings", and added the path to the user settings. As someone
who had never used VS Code this was very confusing. Then I had to
configure and try multiple different C++ syntax extensions. The first
one I tried was the C++ by Microsoft, gave up on that in like 3 mins.
Then tried LLVM but didn\'t understand the whole "server" thing so I
moved on. ClangD was the one that finally worked for me. It worked
pretty well and I was able to use CMake tools to configure my project
after making sure it was using the workspace folder. This make no sense
because you can have multiple parallel workspace folders but I told it
where to find "CMakeLists.txt".
![](.//media/image4.png){width="2.0781255468066493in"
height="0.7959481627296588in"}

If you plan on building AAX just know it is a giant pain. First I would
go and register as a Dev through AVID. After that you should email AVID
and ask for PACE license software and Pro tools DEV license. You'll have
to follow some of their instructions that I am legally not allowed to
mention. Not too hard to do but the issue is that you have to sign your
AAX bundle so that it will work in Pro tools and there is not many
people you can ask for questions. One thing I discovered is that you DO
NOT NEED an Apple Dev account. Self signing is an option: Keychain
access menu (in top left)> Certificate Assistant> Create Certificate
Authority> Change setting to "Code signing" and put the name as
"Developer ID Application: \[Company name\]". You will be asked for this
name later. You can export the Key to a .p12 file for signing on windows
(you cannot sign a windows package on mac).

There are lots of Juce tutorials so I won't go over that except for the
issues I ran into. First thing is if any variable crosses from your
Audio processor to Editor or vise versa, MAKE IT ATOMIC.
std::atomic\<type> fixed a bunch of issues for me. Another issue I ran
into was that there are hard limits to memory which if you don't know
what you're doing, you will hit. I wanted a reverb effect so I saved the
buffer into audioblocks. I thought it could handle 100 of these but as
it turns out; no... Each buffer is 512 for my setting which meant I was
saving 51200 samples in memory at any given time. Which also overflowed
the sample rate, which I have no idea how that also messed things up. I
ended up saving one sample per buffer and using it later to manipulate
the distortion for each block.
![](.//media/image11.jpg){width="2.0989588801399823in"
height="2.0989588801399823in"}

Do yourself a favor and get a DSP or trigonometry book that can help you
with graphing equations. I had to do a bunch of trial and error because
I only took trig in HS. Another headache was discovering that CMAKE was
not gonna work on windows without lots of issues. I think it had to do
with where all the folders were located and how my juce folder was not
nearby. Finally I gave up and used Visual Studio. I discovered that it
does not recursively search paths. You need to drill down to every file
you need and understand the file structure in how they reference each
other. Windows gave me many other headaches. For instance, if you want
to downscale your image, just don\'t do it on windows. It looks great on
mac when you take a 1000x1000 and down scale it to 200x200. OpenGl
doesn't help, setting the resampling quality does nothing, just save the
headache and export it at a smaller size. Use IF statements to make it
use the correct image for what size you need.

For testing make sure you use DBG(var or "string") as std::cout wont
always work. I also found this great tool by Tracktion:
[[https://github.com/Tracktion/pluginval]{.underline}](https://github.com/Tracktion/pluginval).
This tool tests your plugin to make sure it will work on all different
sample rates. When exporting on MAC, if you have M1, make sure your
target is only x86/64 so that you don't get error like "Unknown
exporter" and stuff like that.

Packaging your plugin is a nightmare, I used Packages for mac and I have
included some of those files in the code. Check the PKG folder.

I am definitely going to make more plugins now that I have learned about
code, compiling, DSP, and cross platform compatibility. Here is a list
of things you need if you want to create plugins using JUCE too:

-   JUCE

-   VSCODE:

    -   FRUT

    -   Cmake tools

    -   Cmake

    -   ClangD

    -   Patience\...

-   The platform you want to build for. (Windows, Mac, or Linux)

-   Avid dev account (Takes time to get approved, it helps if you have a
    > brand or company with a company email or else they probably wont
    > give you these things) email: devauth\@avid.com

    -   Pace license software

    -   Dev/Beta Pro tools license

    -   Avid SDK

    -   Build the Avid sdk library for each platform

-   Plugin tester:
    > [[https://github.com/Tracktion/pluginval]{.underline}](https://github.com/Tracktion/pluginval)

-   An understanding of Github (Commits and stuff)

-   DSP book

-   C++ Book (I recommend C++ Primer 5th ed by Stanley Lippman)

-   Package installer creation tool for each Platform

I made this plugin and guide for free and would love it if you could
help out by donating:
[[https://www.paypal.com/donate?hosted_button_id=9ELH753DDE98Y]{.underline}](https://www.paypal.com/donate?hosted_button_id=9ELH753DDE98Y)

Review it on these websites so more people will come get this free
plugin:

TBD

**Jonathan Stoff**

*Owner of Stoff Audio LLC*

Email: Stoffaudio\@gmail.com

![](.//media/image2.jpg){width="1.734375546806649in"
height="1.734375546806649in"}

[Website](https://jonathanstoff.wixsite.com/stoffaudio) \|
[Music](https://open.spotify.com/artist/6g5lKBY6AaHlECDPOqbmiM?si=YPCEy3QJQ2mQlYHuNb6yLw)
\| [Other Links](https://linktr.ee/stoffaudio)
