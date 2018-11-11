require "fileutils"
require "optparse"
require "rexml/document"

# NilClass extensions
class NilClass
  def nilOrEmpty?
    true
  end
end

# String extensions
class String
  def unixPath()
    self.gsub('\\', '/')
  end
  def windowsPath()
    self.gsub('/', '\\')
  end
  def startsWith?(start)
    return (self[0...(start.length)] == start)
  end
  def endsWith?(ends)
    return (self[(-ends.length)..-1] == ends)
  end
  def nilOrEmpty?
	return (self.to_s.strip.length == 0)
  end
end

# Globals
cmd_dir = Dir.pwd.unixPath

# Report errors and exit
def exit_on_error(message)
	puts message
	puts "Aborting... you have to restore your repository with 'git revert'"
	exit
end

# Report missing option and exit
def exit_on_missing_option(message)
	puts message
	puts "Use -h for help."
	puts "Aborting..."
	exit
end

# Check input
def check_input(input)
	if(!File.file?(input))
		exit_on_error("ERROR! check_input: Cannot find input. File '" + input + "' is missing.")
	end
end

# Copy header to markdown report
def copy_header_to_markdown_report(md_file, template)
	if(File.file?(template))
		File.readlines(template).each do |line|
            md_file.puts(line)
        end
	end
end

# Generate markdown report summary
def generate_markdown_report_summary(xml_report, md_file)
    md_file.puts("")
    md_file.puts("# Summary")
    md_file.puts("")
    xml_testsuites = REXML::XPath.first(xml_report, "/testsuites")
    md_file.puts("Test suites *" + xml_testsuites.attributes["name"].to_s + "* with " + xml_testsuites.attributes["tests"].to_s + " test cases was executed " + xml_testsuites.attributes["timestamp"].to_s.gsub('T', ' at ') + " with result:")
    md_file.puts("")
    md_file.puts("* " + xml_testsuites.attributes["errors"].to_s + " errors")
    md_file.puts("* " + xml_testsuites.attributes["failures"].to_s + " failures")
    md_file.puts("")
    md_file.puts("Test suites execution took " + xml_testsuites.attributes["time"].to_s + " seconds.")
    if xml_testsuites.attributes["disabled"].to_i > 0
        md_file.puts("")
        md_file.puts(xml_testsuites.attributes["disabled"].to_s + " test cases were disabled.")
    end
end

# Generate markdown report testcase failure
def generate_markdown_report_testcase_failure(xml_report_testcase, md_file)
    failure_message = ""
    xml_report_testcase.elements.each("failure") do |xml_failure|
        failure_at = xml_failure.attributes["message"].to_s.match /.*(go_libs.*\.cpp\:\d+)/
        if failure_at != nil
            failure_message += failure_at[1].to_s + "; "
        end
    end
    md_file.puts(xml_report_testcase.attributes["name"].to_s + " | " + xml_report_testcase.attributes["time"].to_s + " | " + failure_message.chomp("; ").unixPath)
end

# Generate markdown report testcase success
def generate_markdown_report_testcase_success(xml_report_testcase, md_file)
    md_file.puts(xml_report_testcase.attributes["name"].to_s + " | " + xml_report_testcase.attributes["time"].to_s)
end

# Generate markdown report testcase disabled
def generate_markdown_report_testcase_disabled(xml_report_testcase, md_file)
    md_file.puts("* " + xml_report_testcase.attributes["name"].to_s)
end

# Generate markdown report testsuite
def generate_markdown_report_testsuite(xml_report_testsuite, md_file)
    md_file.puts("## " + xml_report_testsuite.attributes["name"].to_s)
    md_file.puts("")
    md_file.puts("Test suite *" + xml_report_testsuite.attributes["name"].to_s + "* with " + xml_report_testsuite.attributes["tests"].to_s + " test cases was executed with result:")
    md_file.puts("")
    md_file.puts("* " + xml_report_testsuite.attributes["errors"].to_s + " errors")
    md_file.puts("* " + xml_report_testsuite.attributes["failures"].to_s + " failures")
    md_file.puts("")
    md_file.puts("Test suite execution took " + xml_report_testsuite.attributes["time"].to_s + " seconds.")
    if xml_report_testsuite.attributes["disabled"].to_i > 0
        md_file.puts("")
        md_file.puts(xml_report_testsuite.attributes["disabled"].to_s + " test cases were disabled.")
    end
    failed_testcases = 0
    if xml_report_testsuite.attributes["failures"].to_i > 0
        md_file.puts("")
        md_file.puts("### Failed test cases")
        md_file.puts("")
        md_file.puts("Test case|Execution time|Failure at line")
        md_file.puts("-|-|-")
        xml_report_testsuite.elements.each("testcase") do |xml_testcase|
            xml_testcase_failures = xml_testcase.get_elements("failure")
            if xml_testcase_failures.size > 0 and xml_testcase.attributes["status"].to_s.eql? "run"
                failed_testcases += 1
                generate_markdown_report_testcase_failure(xml_testcase, md_file)
            end
        end
    end
    if xml_report_testsuite.attributes["tests"].to_i > failed_testcases
        md_file.puts("")
        md_file.puts("### Successful test cases")
        md_file.puts("")
        md_file.puts("Test case|Execution time")
        md_file.puts("-|-")
        xml_report_testsuite.elements.each("testcase") do |xml_testcase|
            xml_testcase_failures = xml_testcase.get_elements("failure")
            if xml_testcase_failures.size == 0 and xml_testcase.attributes["status"].to_s.eql? "run"
                generate_markdown_report_testcase_success(xml_testcase, md_file)
            end
        end
    end
    if xml_report_testsuite.attributes["disabled"].to_i > 0
        md_file.puts("")
        md_file.puts("### Disabled test cases")
        md_file.puts("")
        xml_report_testsuite.elements.each("testcase") do |xml_testcase|
            if xml_testcase.attributes["status"].to_s.eql? "notrun"
                generate_markdown_report_testcase_disabled(xml_testcase, md_file)
            end
        end
    end
end

# Generate markdown report testsuites
def generate_markdown_report_testsuites(xml_report, md_file)
    md_file.puts("")
    md_file.puts("# Details")
    xml_report.elements.each("/testsuites/testsuite") do |xml_testsuite|
        md_file.puts("")
        generate_markdown_report_testsuite(xml_testsuite, md_file)
    end
end

# Generate markdown report
def generate_markdown_report(xml_report, md_file)
    generate_markdown_report_summary(xml_report, md_file)
    generate_markdown_report_testsuites(xml_report, md_file)
end

# Check options
options = {}
OptionParser.new do |opts|
	opts.banner = "Usage: gtest_xml_report_to_markdown.rb [options]"
	opts.on("-i", "--input INPUT", "Mandatory: Input file name, e.g. report.xml") { |v| options[:input] = v.unixPath }
	opts.on("-o", "--output OUTPUT", "Mandatory: Output file name, e.g. report.md") { |v| options[:output] = v.unixPath }
	opts.on("-h", "--help", "Show this help message.") { puts opts; exit }
	opts.on("-t", "--template TEMPLATE", "Optional: Header template for the markdown report, e.g. report_header.md") { |v| options[:template] = v }
end.parse!
if options[:input] == nil
	exit_on_missing_option("Input file name must be given.")
end
if options[:output] == nil
	exit_on_missing_option("Output file name must be given.")
end

# Check input
xml_source_filename = options[:input].to_s.unixPath
check_input(xml_source_filename)

# Copy input XML report to output dir
xml_source_copy_filename = options[:output].to_s.unixPath.gsub(".md", ".xml")
if File.file?(xml_source_copy_filename)
    FileUtils.rm_f(xml_source_copy_filename)
end
FileUtils.cp(xml_source_filename, xml_source_copy_filename)

# Read XML report
xml_report = File.open(xml_source_filename) { |xml_file| REXML::Document.new(xml_file) }

# Create markdown report
md_filename = options[:output].to_s.unixPath
md_file = File.open(md_filename, "w+")

# Copy header to markdown report
md_template_filename = options[:template].to_s.unixPath
copy_header_to_markdown_report(md_file, md_template_filename)

# Generate markdown report
generate_markdown_report(xml_report, md_file)
